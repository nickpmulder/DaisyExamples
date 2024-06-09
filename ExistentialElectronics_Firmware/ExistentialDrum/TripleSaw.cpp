//cronch firmware 1.1
#include "daisy_patch_sm.h"
#include "daisysp.h"


using namespace daisy;
using namespace patch_sm;
using namespace daisysp;

DaisyPatchSM patch;
Oscillator   osc_a, osc_b, osc_c;
WhiteNoise   noise;
Wavefolder fold;
AdEnv pitch_envelope;
AdEnv amp_envelope;
AdEnv amp_envelope_noise;
Overdrive drive;
Switch button1;
Switch button2;
Switch button3;
Switch button4;
float peak_tune =0;
float fine_tune =0;
float coarse_tune =0;
float waveForm=1;
float noiseAmount=0;
float osc_amp=0;
float LEDlevel=0;


void AudioCallback(AudioHandle::InputBuffer  in,
                   AudioHandle::OutputBuffer out,
                   size_t                    size)
{
    patch.ProcessAllControls();
    button1.Debounce();
    button2.Debounce();
    button3.Debounce();
    button4.Debounce();





 if(button3.RisingEdge() || button2.RisingEdge())
       { amp_envelope.Trigger();
        pitch_envelope.Trigger();
                }

 if(button1.RisingEdge() || button4.FallingEdge())
       { waveForm++;
        if (waveForm == 6){waveForm = 1;}
                }

if (waveForm==1){
    osc_a.SetWaveform(Oscillator::WAVE_SIN);
                drive.SetDrive(.3);  
                 //noiseAmount = .0;
                 osc_amp=1.5;
                 fold.SetGain(1);
                LEDlevel=5;
}

if (waveForm==2){
    osc_a.SetWaveform(Oscillator::WAVE_TRI);
                drive.SetDrive(.4);    
                 //noiseAmount = .1;
                 osc_amp=2;
                 fold.SetGain(1);
                LEDlevel=3;


}

if (waveForm==3){
    osc_a.SetWaveform(Oscillator::WAVE_TRI);
            drive.SetDrive(.4);    
             //noiseAmount = .2;
                 osc_amp=1;
                fold.SetGain(2.5);
                LEDlevel=4;


}
if (waveForm==4){
    osc_a.SetWaveform(Oscillator::WAVE_TRI);
            drive.SetDrive(.5);    
             //noiseAmount = .4;
                 osc_amp=1;
                 fold.SetGain(3);
                LEDlevel=2.8;

}

if (waveForm==5){
    osc_a.SetWaveform(Oscillator::WAVE_TRI);
            drive.SetDrive(1);    
             //noiseAmount = .7;
                 osc_amp=1;
                 fold.SetGain(1);
                LEDlevel=3;

}



float knob_coarse = patch.GetAdcValue(CV_5);
     coarse_tune = fmap(knob_coarse, 0, 100);

float knob_peak = patch.GetAdcValue(CV_3);
     peak_tune = fmap(knob_peak, 0, 100);

    /** Get Coarse, Fine, and V/OCT inputs from hardware 
     *  MIDI Note number are easy to use for defining ranges */


float knob_calibrate = patch.GetAdcValue(CV_6);
     float calibrate = fmap(knob_calibrate, 0, 30);

float cv_voct = patch.GetAdcValue(CV_8);
    float voct    = fmap(cv_voct, 0,160+calibrate);



float noise_knob = patch.GetAdcValue(CV_1);
    float noiseAmount    = fmap(noise_knob, 0,4);

    float knob_pitch_decay = patch.GetAdcValue(CV_2);
    pitch_envelope.SetTime(ADENV_SEG_ATTACK, .01);
    pitch_envelope.SetTime(ADENV_SEG_DECAY, knob_pitch_decay);


   
    float knob_amp_decay = patch.GetAdcValue(CV_4)*2;
    amp_envelope.SetTime(ADENV_SEG_ATTACK, .01);
    amp_envelope.SetTime(ADENV_SEG_DECAY, knob_amp_decay);


    amp_envelope_noise.SetTime(ADENV_SEG_ATTACK, .01);
    amp_envelope_noise.SetTime(ADENV_SEG_DECAY, knob_amp_decay/2);

  // envelope.SetCurve(20);
    
    /** Process each sample of the oscillator and send to the hardware outputs */
    for(size_t i = 0; i < size; i++)
    {
    /** Convert from MIDI note number to frequency */

    float env_pitch=pitch_envelope.Process();

    float midi_nn = fclamp(fine_tune + coarse_tune + voct+(env_pitch*peak_tune), 0.f, 127.f);
    float freq_a  = mtof(midi_nn);



    osc_a.SetFreq(freq_a);




    float env_amp=amp_envelope.Process();
   

   // osc_a.SetAmp(osc_amp);
    //noise.SetAmp(env_amp);


        float sigA = osc_a.Process();


        float sigL= fold.Process(drive.Process(sigA+noise.Process()*noiseAmount));
        

 
        OUT_L[i]  = (sigL)*env_amp*osc_amp;


        patch.WriteCvOut(CV_OUT_1, (sigL)*env_amp*LEDlevel);
        patch.WriteCvOut(CV_OUT_2, (sigL)*env_amp*LEDlevel);

    }
}

int main(void)
{
    patch.Init();


    button1.Init(patch.D6);
    button2.Init(patch.D7);
    button3.Init(patch.B10);
    button4.Init(patch.D4);

    amp_envelope.Init(48000);
    pitch_envelope.Init(48000);
    amp_envelope_noise.Init(48000);

    noise.Init();



    osc_a.Init(patch.AudioSampleRate());
   // osc_b.Init(patch.AudioSampleRate());
    //osc_c.Init(patch.AudioSampleRate());
    
    



    patch.StartAudio(AudioCallback);
    while(1) {}
}
