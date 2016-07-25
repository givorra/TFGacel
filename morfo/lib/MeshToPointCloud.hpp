#ifndef MESHTOPOINTCLOUD_HPP_
#define MESHTOPOINTCLOUD_HPP_

#include <boost/random.hpp>
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int_distribution.hpp>

#include <pcl/common/transforms.h>
#include <pcl/filters/voxel_grid.h>
#include <pcl/point_types.h>
#include <pcl/visualization/pcl_visualizer.h>

#include <vtkPLYReader.h>

class MeshToPointCloud
{
	public:

		MeshToPointCloud() {}

		void sample_mesh_raytracing (
				const pcl::PointCloud<pcl::PointXYZ>::Ptr cpMeshCloud,
				const std::vector<pcl::Vertices> & crMeshFaces,
				pcl::PointCloud<pcl::PointXYZ>::Ptr pCloud)
		{
			pCloud->clear();

			int tesselated_sphere_level_ = 2;
			int resolution_ = 100;
			float leaf_size_ = 0.1f;

			vtkSmartPointer<vtkPolyData> vtk_mesh_data_ = vtkSmartPointer<vtkPolyData>::New();

			// Load mesh vertices into vtk data
			vtkSmartPointer<vtkPoints> vtk_mesh_points_ = vtkSmartPointer<vtkPoints>::New();
			vtk_mesh_points_->SetNumberOfPoints(cpMeshCloud->points.size());
			for (size_t i = 0; i < cpMeshCloud->points.size(); ++i)
				vtk_mesh_points_->SetPoint(	i, 
																		cpMeshCloud->points[i].x, 
																		cpMeshCloud->points[i].y,
																		cpMeshCloud->points[i].z);

			vtk_mesh_data_->SetPoints(vtk_mesh_points_);

			// Load mesh faces into vtk data
			vtkSmartPointer<vtkCellArray> vtk_mesh_polys_ = vtkSmartPointer<vtkCellArray>::New();
			for (size_t i = 0; i < crMeshFaces.size(); ++i)
			{
				vtkIdType a_ = crMeshFaces[i].vertices[0];
				vtkIdType b_ = crMeshFaces[i].vertices[1];
				vtkIdType c_ = crMeshFaces[i].vertices[2];

				vtk_mesh_polys_->InsertNextCell(3);
				vtk_mesh_polys_->InsertCellPoint(a_);
				vtk_mesh_polys_->InsertCellPoint(b_);
				vtk_mesh_polys_->InsertCellPoint(c_);
			}

			vtk_mesh_data_->SetPolys(vtk_mesh_polys_);

			// Sampling
			pcl::visualization::PCLVisualizer visualizer_;
            visualizer_.addModelFromPolyData(vtk_mesh_data_, "mesh1", 0);
			visualizer_.setRepresentationToSurfaceForAllActors();

			pcl::PointCloud<pcl::PointXYZ>::CloudVectorType views_xyz_;
			std::vector<Eigen::Matrix4f, Eigen::aligned_allocator<Eigen::Matrix4f>> poses_;
			std::vector<float> enthropies_;
			visualizer_.renderViewTesselatedSphere(resolution_, 
																			resolution_, 
																			views_xyz_, 
																			poses_, 
																			enthropies_,
																			tesselated_sphere_level_);

			// Fuse clouds
			for (size_t i = 0; i < views_xyz_.size(); ++i)
			{
				pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_(new pcl::PointCloud<pcl::PointXYZ>());
				Eigen::Matrix4f pose_inverse_ = poses_[i].inverse();
				pcl::transformPointCloud(views_xyz_[i], *cloud_, pose_inverse_);
				*pCloud += *cloud_;
			}

			// Downsample final cloud
			/*pcl::VoxelGrid<pcl::PointXYZ> vg_;
			vg_.setInputCloud(pCloud);
			vg_.setLeafSize(leaf_size_, leaf_size_, leaf_size_);
			vg_.filter(*pCloud);*/
		}

		void sample_mesh (
				const pcl::PointCloud<pcl::PointXYZ>::Ptr cpMeshCloud,
				const std::vector<pcl::Vertices> & crMeshFaces,
				pcl::PointCloud<pcl::PointXYZ>::Ptr pCloud,
				const int & crSamples)
		{
			pCloud->clear();

			// Calculate cumulative distribution based on the area of the triangles
			// to pick faces with bigger surface with higher probability
			#ifdef DEBUG_INFORMATION
				std::cout << "Calculating triangle areas...\n";
			#endif

			std::vector<double> areas_;
			for (int i = 0; i < crMeshFaces.size(); ++i)
				areas_.push_back(calculate_triangle_area(	cpMeshCloud->points[crMeshFaces[i].vertices[0]],
																									cpMeshCloud->points[crMeshFaces[i].vertices[1]],
																									cpMeshCloud->points[crMeshFaces[i].vertices[2]]));

			double minimum_area_ = std::numeric_limits<double>::max();
			for (int i = 0; i < areas_.size(); ++i)
				if (areas_[i] < minimum_area_)
					minimum_area_ = areas_[i];

			for (int i = 0; i < areas_.size(); ++i)
				areas_[i] /= minimum_area_;

			std::vector<int> cdf_;
			for (int i = 0; i < areas_.size(); ++i)
				for (int j = 0; j < areas_[i]; ++j)
					cdf_.push_back(i);

			// Pick faces to sample and add sampled points to final point cloud
			#ifdef DEBUG_INFORMATION
				std::cout << "Sampling triangular faces...\n";
			#endif

			boost::random::mt19937 gen_;
			boost::random::uniform_int_distribution<> dist_(0, cdf_.size()-1);

			for (int i = 0; i < crSamples; ++i)
			{
				// Pick face to sample out of the cumulative distribution function
				size_t face_ = dist_(gen_);
				// Randomly sample the picked triangle
				pcl::PointXYZ sample_ = sample_triangle(	cpMeshCloud->points[crMeshFaces[cdf_[face_]].vertices[0]],
																									cpMeshCloud->points[crMeshFaces[cdf_[face_]].vertices[1]],
																									cpMeshCloud->points[crMeshFaces[cdf_[face_]].vertices[2]]);
				pCloud->push_back(sample_);
			}

			#ifdef DEBUG_INFORMATION
				std::cout << "Cloud sampled, " << pCloud->points.size() << " points...\n";
			#endif

			(*pCloud) += (*cpMeshCloud);
		}

	private:

		pcl::PointXYZ sample_triangle (
				const pcl::PointXYZ & crA,
				const pcl::PointXYZ & crB,
				const pcl::PointXYZ & crC)
		{
			pcl::PointXYZ point_;
			boost::mt19937 gen_;
			boost::uniform_01<boost::mt19937> dist_(gen_);

			float u_ = dist_();
			float v_ = dist_();

			if (u_ + v_ > 1)
			{
				u_ = 1.0f - u_;
				v_ = 1.0f - v_;
			}

			point_.x = u_ * crA.x + v_ * crB.x + (1.0f - (u_ + v_)) * crC.x;
			point_.y = u_ * crA.y + v_ * crB.y + (1.0f - (u_ + v_)) * crC.y;
			point_.z = u_ * crA.y + v_ * crB.z + (1.0f - (u_ + v_)) * crC.z;

			return point_;
		}

		double calculate_triangle_area (const pcl::PointXYZ & crA, const pcl::PointXYZ & crB, const pcl::PointXYZ & crC)
		{
			double area_ = 0.0;
			pcl::PointXYZ e1_, e2_, e3_;

			e1_.x = crB.x - crA.x;
			e1_.y = crB.y - crA.y;
			e1_.y = crB.z - crA.z;

			e2_.x = crC.x - crA.x;
			e2_.y = crC.y - crA.y;
			e2_.z = crC.z - crA.z;

			e3_.x = e1_.y * e2_.z - e1_.z * e2_.y;
			e3_.y = e1_.z * e2_.x - e1_.x * e2_.z;
			e3_.z = e1_.x * e2_.y - e1_.y * e2_.x;

			area_ = 0.5 * sqrt(e3_.x * e3_.x + e3_.y * e3_.y + e3_.z * e3_.z);

			return area_;
		}
};

#endif
