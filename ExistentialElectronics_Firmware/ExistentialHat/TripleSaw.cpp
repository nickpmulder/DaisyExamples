#include "daisy_patch_sm.h"
#include "daisysp.h"


using namespace daisy;
using namespace patch_sm;
using namespace daisysp;

DaisyPatchSM patch;
Oscillator   osc_a, osc_b, osc_c, osc_d, osc_e, osc_f, osc_g, osc_h, osc_i, osc_j, osc_k, osc_l, osc_m, osc_n;
WhiteNoise   noise;
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
            amp_envelope_noise.Trigger();    
                
                }

//  if(button1.RisingEdge() || button4.FallingEdge())
//        { waveForm++;
//         if (waveForm == 6){waveForm = 1;}
//                 }

// if (waveForm==1){
//     osc_a.SetWaveform(Oscillator::WAVE_SIN);
//                 drive.SetDrive(.2);  
//                  //noiseAmount = .0;

// }

// if (waveForm==2){
//     osc_a.SetWaveform(Oscillator::WAVE_TRI);
//                 drive.SetDrive(.3);    
//                  //noiseAmount = .1;


// }

// if (waveForm==3){
//     osc_a.SetWaveform(Oscillator::WAVE_TRI);
//             drive.SetDrive(.4);    
//              //noiseAmount = .2;

// }
// if (waveForm==4){
//     osc_a.SetWaveform(Oscillator::WAVE_TRI);
//             drive.SetDrive(.5);    
//              //noiseAmount = .4;

// }

// if (waveForm==5){
//     osc_a.SetWaveform(Oscillator::WAVE_TRI);
//             drive.SetDrive(.8);    
//              //noiseAmount = .7;

// }

osc_a.SetWaveform(Oscillator::WAVE_SQUARE);
osc_b.SetWaveform(Oscillator::WAVE_SQUARE);
osc_c.SetWaveform(Oscillator::WAVE_SQUARE);
osc_d.SetWaveform(Oscillator::WAVE_SQUARE);
osc_e.SetWaveform(Oscillator::WAVE_SQUARE);
osc_f.SetWaveform(Oscillator::WAVE_SQUARE);
osc_g.SetWaveform(Oscillator::WAVE_SQUARE);
osc_h.SetWaveform(Oscillator::WAVE_SQUARE);
osc_i.SetWaveform(Oscillator::WAVE_SQUARE);
osc_j.SetWaveform(Oscillator::WAVE_SQUARE);
osc_k.SetWaveform(Oscillator::WAVE_SQUARE);
osc_l.SetWaveform(Oscillator::WAVE_SQUARE);
osc_m.SetWaveform(Oscillator::WAVE_SQUARE);
osc_n.SetWaveform(Oscillator::WAVE_SQUARE);

float knob_coarse = patch.GetAdcValue(CV_5);
     coarse_tune = fmap(knob_coarse, 0, 350);



    /** Get Coarse, Fine, and V/OCT inputs from hardware 
     *  MIDI Note number are easy to use for defining ranges */


float knob_calibrate = patch.GetAdcValue(CV_6);
     float calibrate = fmap(knob_calibrate, 0, 30);

float cv_voct = patch.GetAdcValue(CV_8);
    float voct    = fmap(cv_voct, 0,160+calibrate);



float noise_knob = patch.GetAdcValue(CV_1);
    float noiseAmount    = fmap(noise_knob, 0,4);

float knob_detune = patch.GetAdcValue(CV_2);
    float detuneAmount = fmap(knob_detune, .5, 20);



   
float knob_amp_decay = patch.GetAdcValue(CV_4)*2;
    amp_envelope.SetTime(ADENV_SEG_ATTACK, .01);
    amp_envelope.SetTime(ADENV_SEG_DECAY, knob_amp_decay);

float knob_noise_decay = patch.GetAdcValue(CV_3)*2;
    amp_envelope_noise.SetTime(ADENV_SEG_ATTACK, .01);
    amp_envelope_noise.SetTime(ADENV_SEG_DECAY, knob_noise_decay);

  // envelope.SetCurve(20);
    
    /** Process each sample of the oscillator and send to the hardware outputs */
    for(size_t i = 0; i < size; i++)
    {
    /** Convert from MIDI note number to frequency */

   // float env_pitch=pitch_envelope.Process();

    float midi_nn = fclamp(fine_tune + coarse_tune + voct, 0.f, 127.f);
        float freq_a  = mtof(midi_nn);
        float freq_b = freq_a*(1.05*detuneAmount);
        float freq_c = freq_a*(1.11*detuneAmount);
        float freq_d = freq_a*(1.13*detuneAmount);
        float freq_e = freq_a*(1.15*detuneAmount);
        float freq_f = freq_a*(1.21*detuneAmount);
        float freq_g = freq_a*(1.24*detuneAmount);
        float freq_h = freq_a*(1.27*detuneAmount);
        float freq_i = freq_a*(1.31*detuneAmount);
        float freq_j = freq_a*(1.33*detuneAmount);
        float freq_k = freq_a*(1.36*detuneAmount);
        float freq_l = freq_a*(1.38*detuneAmount);
        float freq_m = freq_a*(1.42*detuneAmount);
        float freq_n = freq_a*(1.43*detuneAmount);


    osc_a.SetFreq(freq_a);
    osc_b.SetFreq(freq_b);
    osc_c.SetFreq(freq_c);
    osc_d.SetFreq(freq_d);
    osc_e.SetFreq(freq_e);
    osc_f.SetFreq(freq_f);
    osc_g.SetFreq(freq_g);
    osc_h.SetFreq(freq_h);
    osc_i.SetFreq(freq_i);
    osc_j.SetFreq(freq_j);
    osc_k.SetFreq(freq_k);
    osc_l.SetFreq(freq_l);
    osc_m.SetFreq(freq_m);
    osc_n.SetFreq(freq_n);



    float env_amp=amp_envelope.Process();
    float env_amp_noise=amp_envelope_noise.Process();


    //osc_a.SetAmp(env_amp);
    //noise.SetAmp(env_amp);


        float sigA = 
         osc_a.Process()*.2
        +osc_b.Process()*.2
        +osc_c.Process()*.2
        +osc_d.Process()*.2
        +osc_e.Process()*.2
        +osc_f.Process()*.2
        +osc_g.Process()*.2
        +osc_h.Process()*.2
        +osc_i.Process()*.2
        +osc_j.Process()*.2
        +osc_k.Process()*.2
        +osc_l.Process()*.2
        +osc_m.Process()*.2
        +osc_n.Process()*.2

        ;

float sigB= noise.Process()*noiseAmount;

        //float sigL= drive.Process(sigA+noise.Process()*noiseAmount);
        
float sigC = sigA*env_amp + sigB*env_amp_noise;
 
        OUT_L[i]  = sigC;


        patch.WriteCvOut(CV_OUT_1, (sigA)*env_amp*5);
        patch.WriteCvOut(CV_OUT_2, (sigA)*env_amp*5);

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
    osc_b.Init(patch.AudioSampleRate());
    osc_c.Init(patch.AudioSampleRate());
    osc_d.Init(patch.AudioSampleRate());
    osc_e.Init(patch.AudioSampleRate());
    osc_f.Init(patch.AudioSampleRate());
    osc_g.Init(patch.AudioSampleRate());
    osc_h.Init(patch.AudioSampleRate());
    osc_i.Init(patch.AudioSampleRate());
    osc_j.Init(patch.AudioSampleRate());
    osc_k.Init(patch.AudioSampleRate());
    osc_l.Init(patch.AudioSampleRate());
    osc_m.Init(patch.AudioSampleRate());
    osc_n.Init(patch.AudioSampleRate());

    



    patch.StartAudio(AudioCallback);
    while(1) {}
}
