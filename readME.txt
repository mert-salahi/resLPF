Contents:

	resLPF - The project folder generated with JUCE. I've been compiling the plug-in as a VST.
	mertIIR.py - a helpful python script I used to prototype/sketch out the filter design.

Potential Improvements:
	The filter is based off a second-order resonator. Two zeros are placed at Fs/2 in the z-plane, and a pair of conjugate poles are determined by 		the resonance and cutoff frequency. Transposed direct form II was used as the implementation of the IIR filter. A better approach might be to 		model an analog filter, i.e. Chebyshev or SVF, and then translate to a digital implementation via bilinear transform.

	I made the decision to update the filter coefficients every buffer. Updating on an every sample basis would be achievable with some averaging on 	the values from the GUI controls. Some of the other filter implementations described above would also be better suited for quick adjustment of 		cutoff frequency and resonance/Q.

	I spelled "coefficients" wrong in the code...
