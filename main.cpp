/*
This module applies the offset [ -13  +50  0] to the Top-heading-west scanner to compensate for misalignment between the two pointclouds.
Input file: XXXXXXX--Top-heading-west_0.ply

*/

#include <iostream>
#include <pcl/io/pcd_io.h>
#include <pcl/io/ply_io.h>
#include <pcl/point_cloud.h>
#include <pcl/console/parse.h>
#include <pcl/common/transforms.h>
#include <pcl/visualization/pcl_visualizer.h>
#include <pcl/point_types.h>

using namespace std;
using namespace pcl;

int main (int argc, char** argv)
{
	//Defined offset
	double X_shift=-13;
	double Y_shift= 50;

	std::vector<int> filenames;
	// inputfile --> Top-heading-west
	filenames = pcl::console::parse_file_extension_argument (argc, argv, ".ply");
	if (argc<2)
	{
		std::cout << "Input PLY file is missing" << endl;
		return -1;
	}

	// Load file
	pcl::PointCloud<pcl::PointXYZ>::Ptr source_cloud (new pcl::PointCloud<pcl::PointXYZ> ());
	if (pcl::io::loadPLYFile (argv[filenames[0]], *source_cloud) < 0)
	 {
		std::cout << "Error loading point cloud " << argv[filenames[0]] << std::endl << std::endl;

		return -1;
	}
        std::string Name = argv[filenames[0]];
	std::size_t check= Name.find("Top-heading-west");

	if (check==std::string::npos)
	{
		std::cout << "The transformation should be applied to Top--heading-west scanner" << endl ;
		return -1;
	}


	// Define a translation of "X_shift" on the x axis and "Y_shift" on the y axis.
	Eigen::Affine3f transformation = Eigen::Affine3f::Identity();
	transformation (0,3) = X_shift; // shift in the x direction
	transformation (1,3) = Y_shift; //shift in the y direction

	// Executing the transformation
	pcl::PointCloud<pcl::PointXYZ>::Ptr transformed_cloud (new pcl::PointCloud<pcl::PointXYZ>() );
	pcl::transformPointCloud (*source_cloud, *transformed_cloud, transformation);

	// Write back the pointcloud file
	std:: string Output_Filename = Name.substr(0,Name.find(".",0));
	//pcl::io::savePLYFileBinary (Output_Filename.c_str() + std::string("_transformed.ply") , *transformed_cloud);
	pcl::PLYWriter writer;
	writer.write(Output_Filename.c_str() + std::string("_transformed.ply"), *transformed_cloud, true, false );
	return 0;
}
