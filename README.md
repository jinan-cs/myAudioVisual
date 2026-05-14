# Realtime Customised Audio Visual Prototype

This project generates CG visual from sound input from the microphone using openframeworks library.

## Features
- High/mid/low frequency-reactive lighting
- Customisable stamp for fun


## Demo
The following is a screenshot while the app is running.
![example](example.png)

Please also check the demo video `demo.mov` to see how it acutally reacts real-time from the microphone input.

At the bottom, the wave form shows a higher sample rate, which is actually the raw FFT extracted before processed into the img version. This servers as a reference for the relatively true wave form.

## Usage

- For Xcode, open the project, and press `commmand`+`R` or click on the Run buttom on the left up corner.
  - If build failed, try using the projectGenerator, update this project while including the required addons.
  - This may require yourself downloading the extra addons from [Kyle Mcdolnad](https://github.com/kylemcdonald)'s repo. 
- For VS Code, try `command`+`shift`+`P` > **build and run task** first.
  - If error occurs or the option is not found, run `make` in the termminal directly and then `make RunRelease` to execute the program. 

Note that the program may ask for permission to asscess the `bin/data` file and the access to the microphone.

## User Interact
- UI: Press `w` key to turn on/off the wave at the bottom.
- Make some noise or play some music in front of microphone!
  - (Note: If the waveform is dead, please check if the microphone is on, and is not blocking the application.)


## Other Inputs Changable by the user
- An image
  - By now, the image need to be changed manually.
  - This will be used to generate the stamp.
  - The input filename is hardcoded in `setup()` in `ofApp.cpp`, can be changed to other filenames. accroding to the user's image.
  - Add your image in `bin/data` , and change the image file name in line `img.load("tab.png");` (`ofApp.cpp`) to yours!
  - The image is expected to have white background with clear blacklines on it, since the program will extract its lines and store it into polyline vector form for the drawing loop. 


## Parameter adjustable by developer
- FFT Sample rate
  - Change the `512` in `fft.setup(512)` in the `setup()` of `ofApp.cpp` to another `pow(2.0,n)`, where larger `n` will result in higher sample rate.
  - The discrete image display may show slightly different after changing this value. It tooks FFT value from the rangeMax of the `fft.bufffer()` for the visual amplitude.


## Technical Details
- The stamp
  - In `setup()` step, project vectorises the given png/jpg from pixel arrays to a array of vertices (to be specific, into `ofxPolyLine` vector). This lowers the overhead for printing the pixels in every draw loop.
  - In runtime, the image will be temparily stored and drawn using the vectorised stamp. 
  - By changing the image in the `data` folder manually, the user can customise what to be the stamp and enjoy the visual effect.

## Required Addons
- openframeworks built-in addons
  - `ofxOpenCV`
- addons by [Kyle Mcdonald](https://github.com/kylemcdonald)
  - [`ofxCv`](https://github.com/kylemcdonald/ofxCv): for simpler img preprocessing for line extraction.
  - [`ofxFft`](https://github.com/kylemcdonald/ofxFft): for capturing and processing the sound into FFT buffer.
