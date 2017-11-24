# Fast Digital Image Inpainting

An implementation of "Fast Digital Image Inpainting" using C++ and OpenCV.

## Requirements
* OpenCV 2.X or higher

## Example Results

From left to right, input, mask, and output (result) with 500 iterations.

* Input: 3-channel color image
* Mask: 3-channel black and white image
* Output: 3-channel color image

![example_1](https://raw.githubusercontent.com/Mugichoko445/Fast-Digital-Image-Inpainting/images/example_1.png)
![example_2](https://raw.githubusercontent.com/Mugichoko445/Fast-Digital-Image-Inpainting/images/example_2.png)
![example_3](https://raw.githubusercontent.com/Mugichoko445/Fast-Digital-Image-Inpainting/images/example_3.png)
![example_4](https://raw.githubusercontent.com/Mugichoko445/Fast-Digital-Image-Inpainting/images/example_4.png)
![example_5](https://raw.githubusercontent.com/Mugichoko445/Fast-Digital-Image-Inpainting/images/example_5.png)

## Notes
Edge-aware inpainting is not implemented.

## Reference

M. M. Oliveira, B. Bowen, R. McKenna, Y.-S. Chang: Fast Digital Image Inpainting, Proc. of Int. Conf. on Visualization, Imaging and Image Processing (VIIP), pp. 261-266, 2001.