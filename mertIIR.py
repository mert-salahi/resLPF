"""example.py
    
    Compute the maximum of a Bessel function and plot it.
    
    """
import argparse
import time
import numpy as np
import scipy
from scipy import signal
import matplotlib.pyplot as plt
import math

class mertIIR:

    def __init__(self, Fs, fc, res):
        self.Fs = Fs
        
        self.a = np.zeros(3)
        self.b = np.zeros(3)
        
        self.s1 = 0.0
        self.s2 = 0.0
        
        self.updateCoeffecients(fc, res)

    #Transposed Direct Form II IIR
    def updateSample(self, newSample):
        #Update output
        out = newSample * self.b[0] * self.s1
        #Update filter memory
        self.s1 = newSample * self.b[1] + self.s2 * - self.a[1] * out
        self.s2 = newSample * self.b[2] - self.a[2] * out
        return out

    # Generate filter coeffecients for second-order lowpass resonator
    def updateCoeffecients(self, newFcutoff, newRes):
        # Determine poles
        r = 1 - newRes*math.sin(math.pi * newFcutoff * 2 / self.Fs)
        self.a[0] = 1
        self.a[1] = -2.0 * r * math.cos(math.pi * newFcutoff * 2 / self.Fs)
        self.a[2] = r*r
        
        # Place zeros at pi or Fs/2
        self.b[0] = 1.0
        self.b[1] = 2.0
        self.b[2] = 1.0

        # Normalize for unity gain at DC
        self.DC_gain = sum(self.b) / sum(self.a)
        self.b[0] /= self.DC_gain
        self.b[1] /= self.DC_gain
        self.b[2] /= self.DC_gain

    def plotFreqResponse(self):
        w, h = signal.freqz(self.b, self.a)

        fig, ax1 = plt.subplots()
        ax1.set_title('Digital filter frequency response')
        ax1.plot(w/math.pi*self.Fs/2, 20 * np.log10(abs(h)), 'b')
        ax1.set_ylabel('Amplitude [dB]', color='b')
        ax1.set_xlabel('Frequency [rad/sample]')
        ax2 = ax1.twinx()
        angles = np.unwrap(np.angle(h))
        ax2.plot(w/math.pi*self.Fs/2, angles, 'g')
        ax2.set_ylabel('Angle (radians)', color='g')
        ax2.grid()
        ax2.axis('tight')
        plt.show()

def main():
    # Parse command-line arguments
    parser = argparse.ArgumentParser(usage=__doc__)
    parser.add_argument("--fc", type=float, default=1000.0, help="Cutoff frequency")
    parser.add_argument("--res", type=float, default=1.0, help="Resonance")
    args = parser.parse_args()
    
    sample_rate = 44100.0
    resLPF_L = mertIIR(sample_rate, args.fc, args.res)
    resLPF_R = mertIIR(sample_rate, args.fc, args.res)
    resLPF_L.plotFreqResponse()
    
    # Generate gaussian white noise, filter, and plot
    mean = 0
    std = 1
    num_samples = 441
    T = num_samples / sample_rate
    t = np.linspace(0, T, num_samples)
    samples = np.random.normal(mean, std, size=num_samples)
    out = signal.lfilter(resLPF_L.b, resLPF_L.a, samples)

    plt.figure
    plt.plot(samples, 'b-*', alpha=0.75)
    plt.plot(out, 'r--')
    plt.legend(('input', 'output'), loc='best')
    plt.grid(True)
    plt.title('Python IIR - Test Signal')
    plt.show()

if __name__ == "__main__":
    main()
