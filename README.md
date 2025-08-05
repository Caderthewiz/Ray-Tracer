# C++ Ray Tracer
This is a ray tracing engine implemented in C++ designed to render photorealistic images. The project includes several advanced features that enhance the realism and performance of the rendered scenes.

## Features
The ray tracer implements anti-aliasing using a multi-sample technique to smooth jagged edges and improve image quality. It supports dielectric materials such as glass and water, accurately simulating light refraction and reflection through Snell’s Law. Defocus blur is implemented to simulate the effect of camera lens apertures, adding a natural depth-of-field effect to the scene. The project also includes motion blur, which captures the movement of objects over time, enhancing the dynamic feel of the rendered images. To improve rendering performance, the ray tracer uses Bounding Volume Hierarchy (BVH) optimization for faster ray-object intersection tests. Texture mapping is supported, allowing realistic image-based textures to be applied to objects and surfaces in the scene. Perlin noise is utilized to generate natural-looking textures and patterns, such as terrains and clouds, for a more organic and dynamic appearance. The ray tracer includes support for multiple light sources, enabling the simulation of realistic scene illumination and shadows. Finally, volumetric smoke is added to create atmospheric effects, enhancing realism by simulating light scattering and absorption within a foggy or smoky environment.

## Results
<img width="1200" height="675" alt="Final Scene 1" src="https://github.com/user-attachments/assets/9a20a62f-9983-48c5-b2fb-d8fdfbafc1ba" />
<img width="400" height="225" alt="Bouncing" src="https://github.com/user-attachments/assets/f1144561-ec63-4065-947d-36a2155713ff" />
<img width="400" height="225" alt="Earth" src="https://github.com/user-attachments/assets/9ee28ea2-14a4-479f-b016-0bf68ce95bba" />
<img width="400" height="225" alt="Light" src="https://github.com/user-attachments/assets/ac15c3e9-d849-404f-a398-d4bb22434049" />
<br>
<img width="600" height="600" alt="Cornell-Box-Smoke" src="https://github.com/user-attachments/assets/54e563a2-1366-4c4a-b9fa-66696264a53f" />
<img width="600" height="600" alt="Cornell-Box" src="https://github.com/user-attachments/assets/6f19907f-df2b-4dee-8549-190a67f9b2be" />
