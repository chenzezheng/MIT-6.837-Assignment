# Assignment for MIT 6.837 Intro to Computer Graphics

`/scene`目录下是所有作业测试的场景文件（输入文件）

`/obj`目录下是所有作业测试的obj文件（输入文件）

`/output`目录下是渲染后的输出图像

`/depth`目录下是深度图像

`/normal`目录下是法向量图像

编译环境`mingw64 & freeglut`

`freeglut`的安装：[freeglut Windows Development Libraries (transmissionzero.co.uk)](https://www.transmissionzero.co.uk/software/freeglut-devel/)



MIT 6.837 Intro to Computer Graphics: [6.837 Course Calendar (mit.edu)](http://groups.csail.mit.edu/graphics/classes/6.837/F04/calendar.html)

目前完成了前5个作业，测试用的命令如下：

[toc]

## Assignment 1: Ray Casting

```bash
raytracer -input scene/scene1_01.txt -size 200 200 -output output/output1_01.tga -depth 9 10 depth/depth1_01.tga
raytracer -input scene/scene1_02.txt -size 200 200 -output output/output1_02.tga -depth 8 12 depth/depth1_02.tga
raytracer -input scene/scene1_03.txt -size 200 200 -output output/output1_03.tga -depth 8 12 depth/depth1_03.tga
raytracer -input scene/scene1_04.txt -size 200 200 -output output/output1_04.tga -depth 12 17 depth/depth1_04.tga
raytracer -input scene/scene1_05.txt -size 200 200 -output output/output1_05.tga -depth 14.5 19.5 depth/depth1_05.tga
raytracer -input scene/scene1_06.txt -size 200 200 -output output/output1_06.tga -depth 3 7 depth/depth1_06.tga
raytracer -input scene/scene1_07.txt -size 200 200 -output output/output1_07.tga -depth -2 2 depth/depth1_07.tga
```



## Assignment 2: Transformations & Additional Primitives

```bash
raytracer -input scene/scene2_01_diffuse.txt -size 200 200 -output output/output2_01.tga
raytracer -input scene/scene2_02_ambient.txt -size 200 200 -output output/output2_02.tga
raytracer -input scene/scene2_03_colored_lights.txt -size 200 200 -output output/output2_03.tga -normals normal/normals2_03.tga
raytracer -input scene/scene2_04_perspective.txt -size 200 200 -output output/output2_04.tga -normals normal/normals2_04.tga
raytracer -input scene/scene2_05_inside_sphere.txt -size 200 200 -output output/output2_05.tga -depth 9 11 depth/depth2_05.tga -normals normal/normals2_05.tga -shade_back
raytracer -input scene/scene2_05_inside_sphere.txt -size 200 200 -output output/output2_05_no_back.tga
raytracer -input scene/scene2_06_plane.txt -size 200 200 -output output/output2_06.tga -depth 8 20 depth/depth2_06.tga -normals normal/normals2_06.tga
raytracer -input scene/scene2_07_sphere_triangles.txt -size 200 200 -output output/output2_07.tga -depth 9 11 depth/depth2_07.tga -normals normal/normals2_07.tga -shade_back
raytracer -input scene/scene2_07_sphere_triangles.txt -size 200 200 -output output/output2_07_no_back.tga
raytracer -input scene/scene2_08_cube.txt -size 200 200 -output output/output2_08.tga
raytracer -input scene/scene2_09_bunny_200.txt -size 200 200 -output output/output2_09.tga
raytracer -input scene/scene2_10_bunny_1k.txt -size 200 200 -output output/output2_10.tga
raytracer -input scene/scene2_11_squashed_sphere.txt -size 200 200 -output output/output2_11.tga -normals normal/normals2_11.tga
raytracer -input scene/scene2_12_rotated_sphere.txt -size 200 200 -output output/output2_12.tga -normals normal/normals2_12.tga
raytracer -input scene/scene2_13_rotated_squashed_sphere.txt -size 200 200 -output output/output2_13.tga -normals normal/normals2_13.tga
raytracer -input scene/scene2_14_axes_cube.txt -size 200 200 -output output/output2_14.tga
raytracer -input scene/scene2_15_crazy_transforms.txt -size 200 200 -output output/output2_15.tga
raytracer -input scene/scene2_16_t_scale.txt -size 200 200 -output output/output2_16.tga -depth 2 7 depth/depth2_16.tga
```



## Assignment 3: OpenGL & Phong Shading

```bash
raytracer -input scene/scene3_01_cube_orthographic.txt -size 200 200 -output output/output3_01.tga -gui
raytracer -input scene/scene3_02_cube_perspective.txt -size 200 200 -output output/output3_02.tga -gui
raytracer -input scene/scene3_03_bunny_mesh_200.txt -size 200 200 -output output/output3_03.tga -gui
raytracer -input scene/scene3_04_bunny_mesh_1k.txt -size 200 200 -output output/output3_04.tga -gui
raytracer -input scene/scene3_05_axes_cube.txt -size 200 200 -output output/output3_05.tga -gui
raytracer -input scene/scene3_06_crazy_transforms.txt -size 200 200 -output output/output3_06.tga -gui
raytracer -input scene/scene3_07_plane.txt -size 200 200 -output output/output3_07.tga -gui -tessellation 10 5
raytracer -input scene/scene3_08_sphere.txt -size 200 200 -output output/output3_08.tga -gui -tessellation 10 5
raytracer -input scene/scene3_08_sphere.txt -size 200 200 -output output/output3_08.tga -gui -tessellation 20 10
raytracer -input scene/scene3_08_sphere.txt -size 200 200 -output output/output3_08.tga -gui -tessellation 10 5 -gouraud
raytracer -input scene/scene3_08_sphere.txt -size 200 200 -output output/output3_08.tga -gui -tessellation 20 10 -gouraud
raytracer -input scene/scene3_09_exponent_variations.txt -size 300 300 -output output/output3_09.tga -gui -tessellation 100 50 -gouraud
raytracer -input scene/scene3_10_exponent_variations_back.txt -size 300 300 -output output/output3_10.tga -gui -tessellation 100 50 -gouraud
raytracer -input scene/scene3_11_weird_lighting_diffuse.txt -size 200 200 -output output/output3_11.tga -gui -tessellation 100 50 -gouraud
raytracer -input scene/scene3_12_weird_lighting_specular.txt -size 200 200 -output output/output3_12.tga -gui -tessellation 100 50 -gouraud
```



## Assignment 4: Shadows, Reflection & Refraction

``` bash
raytracer -input scene/scene4_01_sphere_shadow.txt -size 200 200 -output output/output4_01.tga -shadows
raytracer -input scene/scene4_02_colored_shadows.txt -size 200 200 -output output/output4_02.tga -shadows -gui -tessellation 50 25 -gouraud
raytracer -input scene/scene4_03_mirrored_floor.txt -size 200 200 -output output/output4_03.tga -shadows -bounces 1 -weight 0.01 -gui
raytracer -input scene/scene4_04_reflective_sphere.txt -size 200 200 -output output/output4_04a.tga -shadows -bounces 0 -weight 0.01
raytracer -input scene/scene4_04_reflective_sphere.txt -size 200 200 -output output/output4_04b.tga -shadows -bounces 1 -weight 0.01
raytracer -input scene/scene4_04_reflective_sphere.txt -size 200 200 -output output/output4_04c.tga -shadows -bounces 2 -weight 0.01
raytracer -input scene/scene4_04_reflective_sphere.txt -size 200 200 -output output/output4_04d.tga -shadows -bounces 3 -weight 0.01
raytracer -input scene/scene4_05_transparent_bar.txt -size 200 200 -output output/output4_05.tga -shadows -bounces 10 -weight 0.01 -shade_back -gui
raytracer -input scene/scene4_06_transparent_bars.txt -size 200 200 -output output/output4_06a.tga -shadows -bounces 0 -weight 0.01 -shade_back -gui
raytracer -input scene/scene4_06_transparent_bars.txt -size 200 200 -output output/output4_06b.tga -shadows -bounces 1 -weight 0.01 -shade_back -gui
raytracer -input scene/scene4_06_transparent_bars.txt -size 200 200 -output output/output4_06c.tga -shadows -bounces 2 -weight 0.01 -shade_back -gui
raytracer -input scene/scene4_06_transparent_bars.txt -size 200 200 -output output/output4_06d.tga -shadows -bounces 3 -weight 0.01 -shade_back -gui
raytracer -input scene/scene4_06_transparent_bars.txt -size 200 200 -output output/output4_06e.tga -shadows -bounces 4 -weight 0.01 -shade_back -gui
raytracer -input scene/scene4_06_transparent_bars.txt -size 200 200 -output output/output4_06f.tga -shadows -bounces 5 -weight 0.01 -shade_back -gui
raytracer -input scene/scene4_07_transparent_sphere_1.0.txt -size 200 200 -output output/output4_07.tga -shadows -bounces 5 -weight 0.01 -shade_back -gui -tessellation 30 15
raytracer -input scene/scene4_08_transparent_sphere_1.1.txt -size 200 200 -output output/output4_08.tga -shadows -bounces 5 -weight 0.01 -shade_back -gui -tessellation 30 15
raytracer -input scene/scene4_09_transparent_sphere_2.0.txt -size 200 200 -output output/output4_09.tga -shadows -bounces 5 -weight 0.01 -shade_back -gui -tessellation 30 15
raytracer -input scene/scene4_10_point_light_distance.txt -size 200 200 -output output/output4_10.tga -shadows -gui
raytracer -input scene/scene4_11_point_light_circle.txt -size 200 200 -output output/output4_11.tga -shadows 
raytracer -input scene/scene4_12_point_light_circle_d_attenuation.txt -size 200 200 -output output/output4_12.tga -shadows 
raytracer -input scene/scene4_13_point_light_circle_d2_attenuation.txt -size 200 200 -output output/output4_13.tga -shadows 
raytracer -input scene/scene4_14_faceted_gem.txt -size 200 200 -output output/output4_14a.tga -shadows -shade_back -bounces 0 -weight 0.01 
raytracer -input scene/scene4_14_faceted_gem.txt -size 200 200 -output output/output4_14b.tga -shadows -shade_back -bounces 1 -weight 0.01 
raytracer -input scene/scene4_14_faceted_gem.txt -size 200 200 -output output/output4_14c.tga -shadows -shade_back -bounces 2 -weight 0.01 
raytracer -input scene/scene4_14_faceted_gem.txt -size 200 200 -output output/output4_14d.tga -shadows -shade_back -bounces 3 -weight 0.01 
raytracer -input scene/scene4_14_faceted_gem.txt -size 200 200 -output output/output4_14e.tga -shadows -shade_back -bounces 4 -weight 0.01 
raytracer -input scene/scene4_14_faceted_gem.txt -size 200 200 -output output/output4_14f.tga -shadows -shade_back -bounces 5 -weight 0.01 
raytracer -input scene/scene4_14_faceted_gem.txt -size 200 200 -shadows -shade_back -bounces 1 -weight 0.01 -gui
raytracer -input scene/scene4_14_faceted_gem.txt -size 200 200 -shadows -shade_back -bounces 2 -weight 0.01 -gui
raytracer -input scene/scene4_14_faceted_gem.txt -size 200 200 -shadows -shade_back -bounces 3 -weight 0.01 -gui
```



## Assignment 5: Voxel Rendering

```bash
raytracer -input scene/scene5_01_sphere.txt -size 200 200 -output output/output5_01a.tga -gui -grid 1 1 1 -visualize_grid
raytracer -input scene/scene5_01_sphere.txt -size 200 200 -output output/output5_01b.tga -gui -grid 5 5 5 -visualize_grid
raytracer -input scene/scene5_01_sphere.txt -size 200 200 -output output/output5_01c.tga -gui -grid 15 15 15 -visualize_grid
raytracer -input scene/scene5_02_spheres.txt -size 200 200 -output output/output5_02a.tga -gui -grid 15 15 15 -visualize_grid
raytracer -input scene/scene5_02_spheres.txt -size 200 200 -output output/output5_02b.tga -gui -grid 15 15 3 -visualize_grid
raytracer -input scene/scene5_03_offcenter_spheres.txt -size 200 200 -output output/output5_03.tga -gui -grid 20 20 20 -visualize_grid
raytracer -input scene/scene5_04_plane_test.txt -size 200 200 -gui -tessellation 30 15 -gouraud
raytracer -input scene/scene5_04_plane_test.txt -size 200 200 -output output/output5_04.tga -gui -grid 15 15 15 -visualize_grid
raytracer -input scene/scene5_05_sphere_triangles.txt -size 200 200 -gui -tessellation 30 15 -gouraud
raytracer -input scene/scene5_05_sphere_triangles.txt -size 200 200 -output output/output5_05.tga -gui -grid 20 20 10 -visualize_grid
raytracer -input scene/scene5_06_bunny_mesh_200.txt -size 200 200 -output output/output5_06.tga -gui -grid 10 10 7 -visualize_grid
raytracer -input scene/scene5_07_bunny_mesh_1k.txt -size 200 200 -output output/output5_07.tga -gui -grid 15 15 12 -visualize_grid
raytracer -input scene/scene5_08_bunny_mesh_5k.txt -size 200 200 -output output/output5_08.tga -gui -grid 20 20 15 -visualize_grid
raytracer -input scene/scene5_09_bunny_mesh_40k.txt -size 200 200 -output output/output5_09.tga -gui -grid 40 40 33 -visualize_grid
raytracer -input scene/scene5_10_scale_translate.txt -size 200 200 -gui -tessellation 30 15 -gouraud
raytracer -input scene/scene5_10_scale_translate.txt -size 200 200 -output output/output5_10.tga -gui -grid 15 15 15 -visualize_grid
raytracer -input scene/scene5_11_rotated_triangles.txt -size 200 200 -gui
raytracer -input scene/scene5_11_rotated_triangles.txt -size 200 200 -output output/output5_11.tga -gui -grid 15 15 9 -visualize_grid
raytracer -input scene/scene5_12_nested_transformations.txt -size 200 200 -gui
raytracer -input scene/scene5_12_nested_transformations.txt -size 200 200 -output output/output5_12.tga -gui -grid 30 30 30 -visualize_grid
```



