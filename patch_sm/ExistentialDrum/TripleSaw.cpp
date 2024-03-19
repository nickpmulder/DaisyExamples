#include "daisy_patch_sm.h"
#include "daisysp.h"



using namespace daisy;
using namespace patch_sm;
using namespace daisysp;

DaisyPatchSM patch;
Oscillator   osc_a, osc_b, osc_c;
AdEnv pitch_envelope;
AdEnv amp_envelope;
Switch button1;
Switch button2;
Switch button3;
float peak_tune =0;
float fine_tune =0;
float waveForm=1;

void AudioCallback(AudioHandle::InputBuffer  in,
                   AudioHandle::OutputBuffer out,
                   size_t                    size)
{
    patch.ProcessAllControls();
    button1.Debounce();
    button2.Debounce();
    button3.Debounce();






 if(button3.RisingEdge() || button2.RisingEdge())
       { amp_envelope.Trigger();
        pitch_envelope.Trigger();
                }

osc_a.SetWaveform(Oscillator::WAVE_TRI);


float knob_fine = patch.GetAdcValue(CV_2);
     fine_tune = fmap(knob_fine, 0, 50);

float knob_peak = patch.GetAdcValue(CV_4);
     peak_tune = fmap(knob_peak, 0, 50);

    /** Get Coarse, Fine, and V/OCT inputs from hardware 
     *  MIDI Note number are easy to use for defining ranges */


    float cv_voct = patch.GetAdcValue(CV_7);
        float voct    = fmap(cv_voct, 0, 58.9);



    float knob_pitch_decay = patch.GetAdcValue(CV_6);
    pitch_envelope.SetTime(ADENV_SEG_ATTACK, .01);
    pitch_envelope.SetTime(ADENV_SEG_DECAY, knob_pitch_decay);


   
    float knob_amp_decay = patch.GetAdcValue(CV_8);
    amp_envelope.SetTime(ADENV_SEG_ATTACK, .01);
    amp_envelope.SetTime(ADENV_SEG_DECAY, knob_amp_decay);




  // envelope.SetCurve(20);
    
    /** Process each sample of the oscillator and send to the hardware outputs */
    for(size_t i = 0; i < size; i++)
    {
    /** Convert from MIDI note number to frequency */

    float env_pitch=pitch_envelope.Process();

    float midi_nn = fclamp(fine_tune + voct+(env_pitch*peak_tune), 0.f, 127.f);
    float freq_a  = mtof(midi_nn);




    /** Set all three oscillators' frequencies */
    osc_a.SetFreq(freq_a);
   // osc_b.SetFreq(freq_b);
   // osc_c.SetFreq(freq_c);




    float env_amp=amp_envelope.Process();
    osc_a.SetAmp(env_amp);
    //osc_b.SetAmp(env_out);
    //osc_c.SetAmp(env_out);
        float sigA = osc_a.Process();
      //  float sigB = osc_b.Process();
       // float sigC = osc_c.Process();

        float sigL = (sigA);
        float sigR = (sigA);
        OUT_L[i]  = sigL;
        OUT_R[i]  = sigR;


        patch.WriteCvOut(CV_OUT_1, sigL*5);
        patch.WriteCvOut(CV_OUT_2, sigR*5);

    }
}

int main(void)
{
    patch.Init();


    button1.Init(patch.D6);
    button2.Init(patch.B10);
    button3.Init(patch.D7);

    amp_envelope.Init(48000);
    pitch_envelope.Init(48000);




    osc_a.Init(patch.AudioSampleRate());
   // osc_b.Init(patch.AudioSampleRate());
    //osc_c.Init(patch.AudioSampleRate());
    
    



    patch.StartAudio(AudioCallback);
    while(1) {}
}
