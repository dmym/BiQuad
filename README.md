BiQuad is a C++ audio plugin that implements several IIR filter designs with bi-quad topology.

Supported filtering types: 
LPF, HPF, BPF, BSF.

Implemented designs:
#Generic	 	- common DSP design with resonant peaking
#Butterworth 	- optimally flat amplitude response
#Linkwitz-Riley - attenuation of -6dB instead of standart -3dB

DSP algorithms implemented as separate JUCE module - home_dsp, which should be included via Projucer in settings menu for the project.
Basis for filtering algorithms were taken from the book "Designing Audio Effect Plug-Ins in C++ With Digital Audio Signal Processing Theory " by Will Pirkle

LICENSE
This code is licensed under the terms of the GNU General Public License v3.0 (see the file LICENSE in this repo), inhertited from the JUCE framework. 
