#include "daisy_patch_sm.h"
#include "daisysp.h"


using namespace daisy;
using namespace patch_sm;
using namespace daisysp;

DaisyPatchSM patch;
Oscillator   osc_a, osc_b, osc_c;
WhiteNoise   noise;
AdEnv pitch_envelope;
AdEnv amp_envelope;
Overdrive drive;
Switch button1;
Switch button2;
Switch button3;
float peak_tune =0;
float fine_tune =0;
float coarse_tune =0;
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

//  if(button1.RisingEdge() )
//        { waveForm++;
//         if (waveForm == 4){waveForm = 1;}
//                 }

// if (waveForm==1){
//     osc_a.SetWaveform(Oscillator::WAVE_SIN);
//                 drive.SetDrive(.3);  

// }

// if (waveForm==2){
//     osc_a.SetWaveform(Oscillator::WAVE_TRI);
//                 drive.SetDrive(.4);    

// }

// if (waveForm==3){
//     osc_a.SetWaveform(Oscillator::WAVE_TRI);
//             drive.SetDrive(.5);    

// }

float knob_fine = patch.GetAdcValue(CV_1);
     fine_tune = fmap(knob_fine, 0, 10);

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



    float knob_pitch_decay = patch.GetAdcValue(CV_2);
    pitch_envelope.SetTime(ADENV_SEG_ATTACK, .01);
    pitch_envelope.SetTime(ADENV_SEG_DECAY, knob_pitch_decay);


   
    float knob_amp_decay = patch.GetAdcValue(CV_4)*2;
    amp_envelope.SetTime(ADENV_SEG_ATTACK, .01);
    amp_envelope.SetTime(ADENV_SEG_DECAY, knob_amp_decay);




  // envelope.SetCurve(20);
    
    /** Process each sample of the oscillator and send to the hardware outputs */
    for(size_t i = 0; i < size; i++)
    {
    /** Convert from MIDI note number to frequency */

    float env_pitch=pitch_envelope.Process();

    float midi_nn = fclamp(fine_tune + coarse_tune + voct+(env_pitch*peak_tune), 0.f, 127.f);
    float freq_a  = mtof(midi_nn);
    float freq_b  = freq_a*.87;
    float freq_c  = freq_a*.23;

    osc_a.SetWaveform(Oscillator::WAVE_SQUARE);
    osc_b.SetWaveform(Oscillator::WAVE_SQUARE);
    osc_c.SetWaveform(Oscillator::WAVE_SQUARE);


    /** Set all three oscillators' frequencies */
    osc_a.SetFreq(freq_a);
    osc_b.SetFreq(freq_b);
    osc_c.SetFreq(freq_c);



    float env_amp=amp_envelope.Process();
    osc_a.SetAmp(env_amp);
    osc_b.SetAmp(env_amp);
    osc_c.SetAmp(env_amp);

    noise.SetAmp(env_amp);

    //osc_b.SetAmp(env_out);
    //osc_c.SetAmp(env_out);
       // float sigA = osc_a.Process()+osc_b.Process()+osc_c.Process() ;
float sigA = noise.Process();
      //  float sigB = osc_b.Process();
       // float sigC = osc_c.Process();

        float sigL= drive.Process(sigA);
        float sigR= drive.Process(sigA);

        float sigL1 = (sigL);
        float sigR1 = (sigR);
        OUT_L[i]  = sigL1;
        OUT_R[i]  = sigR1;


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
    noise.Init();



    osc_a.Init(patch.AudioSampleRate());
    osc_b.Init(patch.AudioSampleRate());
    osc_c.Init(patch.AudioSampleRate());
    
    



    patch.StartAudio(AudioCallback);
    while(1) {}
}
