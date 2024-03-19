#include "daisy_patch_sm.h"
#include "daisysp.h"


/** TODO: ADD CALIBRATION */

using namespace daisy;
using namespace patch_sm;
using namespace daisysp;

DaisyPatchSM patch;
Oscillator   osc_a, osc_b, osc_c;
Adsr envelope;
Switch button1;
Switch button2;
Switch button3;
float coarse_tune =0;
float fine_tune =0;
float waveForm=1;
int mode_all=1;
int wave_ind = 0;
float mode_b=1;
float mode_c=1;
int mode_ind=0;
void AudioCallback(AudioHandle::InputBuffer  in,
                   AudioHandle::OutputBuffer out,
                   size_t                    size)
{
    patch.ProcessAllControls();
    button1.Debounce();
    button2.Debounce();
    button3.Debounce();


        bool env_state;

wave_ind++;
mode_ind++;









if(button1.RisingEdge() ){
    
    waveForm=waveForm+1;
    if (waveForm==6){waveForm=1;}

    wave_ind=0;


}

// for (int i = 0; i < waveForm; i++) {

// if (wave_ind == 100+(i*100)){ patch.WriteCvOut(CV_OUT_1, 5);}
// if (wave_ind == 200+(i*100)){ patch.WriteCvOut(CV_OUT_1, 0);}

// }




if (waveForm == 1){
if (wave_ind == 100){ patch.WriteCvOut(CV_OUT_1, 5);}
if (wave_ind == 200){ patch.WriteCvOut(CV_OUT_1, 0);}

}

if (waveForm == 2){

    
if (wave_ind == 100){ patch.WriteCvOut(CV_OUT_1, 5);}
if (wave_ind == 200){ patch.WriteCvOut(CV_OUT_1, 0);}

if (wave_ind == 300){ patch.WriteCvOut(CV_OUT_1, 5);}
if (wave_ind == 400){ patch.WriteCvOut(CV_OUT_1, 0);}   
}


if (waveForm == 3){

    
if (wave_ind == 100){ patch.WriteCvOut(CV_OUT_1, 5);}
if (wave_ind == 200){ patch.WriteCvOut(CV_OUT_1, 0);}

 if (wave_ind == 300){ patch.WriteCvOut(CV_OUT_1, 5);}
if (wave_ind == 400){ patch.WriteCvOut(CV_OUT_1, 0);}  

 if (wave_ind == 500){ patch.WriteCvOut(CV_OUT_1, 5);}
if (wave_ind == 600){ patch.WriteCvOut(CV_OUT_1, 0);} 


}


if (waveForm == 4){

    
if (wave_ind == 100){ patch.WriteCvOut(CV_OUT_1, 5);}
if (wave_ind == 200){ patch.WriteCvOut(CV_OUT_1, 0);}

 if (wave_ind == 300){ patch.WriteCvOut(CV_OUT_1, 5);}
if (wave_ind == 400){ patch.WriteCvOut(CV_OUT_1, 0);}  

 if (wave_ind == 500){ patch.WriteCvOut(CV_OUT_1, 5);}
if (wave_ind == 600){ patch.WriteCvOut(CV_OUT_1, 0);} 


 if (wave_ind == 700){ patch.WriteCvOut(CV_OUT_1, 5);}
if (wave_ind == 800){ patch.WriteCvOut(CV_OUT_1, 0);} 


}






if (waveForm == 5){

    
    
if (wave_ind == 100){ patch.WriteCvOut(CV_OUT_1, 5);}
if (wave_ind == 200){ patch.WriteCvOut(CV_OUT_1, 0);}

if (wave_ind == 300){ patch.WriteCvOut(CV_OUT_1, 5);}
if (wave_ind == 400){ patch.WriteCvOut(CV_OUT_1, 0);}  

if (wave_ind == 500){ patch.WriteCvOut(CV_OUT_1, 5);}
if (wave_ind == 600){ patch.WriteCvOut(CV_OUT_1, 0);} 


if (wave_ind == 700){ patch.WriteCvOut(CV_OUT_1, 5);}
if (wave_ind == 800){ patch.WriteCvOut(CV_OUT_1, 0);} 

if (wave_ind == 900){ patch.WriteCvOut(CV_OUT_1, 5);}
if (wave_ind == 1000){ patch.WriteCvOut(CV_OUT_1, 0);} 
}





    if (waveForm == 1){
    osc_a.SetWaveform(Oscillator::WAVE_SIN);
    osc_b.SetWaveform(Oscillator::WAVE_SIN);
    osc_c.SetWaveform(Oscillator::WAVE_SIN);
        }
    

  
    if (waveForm == 2){
    osc_a.SetWaveform(Oscillator::WAVE_POLYBLEP_SAW);
    osc_b.SetWaveform(Oscillator::WAVE_POLYBLEP_SAW);
    osc_c.SetWaveform(Oscillator::WAVE_POLYBLEP_SAW);
        }




    if (waveForm == 3){
    osc_a.SetWaveform(Oscillator::WAVE_POLYBLEP_SQUARE);
    osc_b.SetWaveform(Oscillator::WAVE_POLYBLEP_SQUARE);
    osc_c.SetWaveform(Oscillator::WAVE_POLYBLEP_SQUARE);
        }

    if (waveForm == 4){
    osc_a.SetWaveform(Oscillator::WAVE_POLYBLEP_SAW);
    osc_b.SetWaveform(Oscillator::WAVE_SIN);
    osc_c.SetWaveform(Oscillator::WAVE_SIN);
        }

    if (waveForm == 5){
    osc_a.SetWaveform(Oscillator::WAVE_POLYBLEP_SQUARE);
    osc_b.SetWaveform(Oscillator::WAVE_POLYBLEP_SAW);
    osc_c.SetWaveform(Oscillator::WAVE_POLYBLEP_SAW);
        }



 if(button2.Pressed())
        env_state = true;
    else
        env_state = false;
 



 if(button3.RisingEdge() ){
    
    mode_all=mode_all+1;
    if (mode_all==5){mode_all=1;}
    mode_ind=0;

}



if (mode_all == 1){
if (mode_ind == 100){ patch.WriteCvOut(CV_OUT_2, 5);}
if (mode_ind == 200){ patch.WriteCvOut(CV_OUT_2, 0);}

}

if (mode_all == 2){

    
if (mode_ind == 100){ patch.WriteCvOut(CV_OUT_2, 5);}
if (mode_ind == 200){ patch.WriteCvOut(CV_OUT_2, 0);}

 if (mode_ind == 300){ patch.WriteCvOut(CV_OUT_2, 5);}
if (mode_ind == 400){ patch.WriteCvOut(CV_OUT_2, 0);}   
}


if (mode_all == 3){

    
if (mode_ind == 100){ patch.WriteCvOut(CV_OUT_2, 5);}
if (mode_ind == 200){ patch.WriteCvOut(CV_OUT_2, 0);}

 if (mode_ind == 300){ patch.WriteCvOut(CV_OUT_2, 5);}
if (mode_ind == 400){ patch.WriteCvOut(CV_OUT_2, 0);}  

 if (mode_ind == 500){ patch.WriteCvOut(CV_OUT_2, 5);}
if (mode_ind == 600){ patch.WriteCvOut(CV_OUT_2, 0);} 


}


if (mode_all == 4){

    
if (mode_ind == 100){ patch.WriteCvOut(CV_OUT_2, 5);}
if (mode_ind == 200){ patch.WriteCvOut(CV_OUT_2, 0);}

 if (mode_ind == 300){ patch.WriteCvOut(CV_OUT_2, 5);}
if (mode_ind == 400){ patch.WriteCvOut(CV_OUT_2, 0);}  

 if (mode_ind == 500){ patch.WriteCvOut(CV_OUT_2, 5);}
if (mode_ind == 600){ patch.WriteCvOut(CV_OUT_2, 0);} 


 if (mode_ind == 700){ patch.WriteCvOut(CV_OUT_2, 5);}
if (mode_ind == 800){ patch.WriteCvOut(CV_OUT_2, 0);} 


}









if (mode_all==1){
     mode_b=1;
     mode_c=1;}

if (mode_all==2){
     mode_b=2;
     mode_c=2;}

if (mode_all==3){
     mode_b=.5;
     mode_c=.5;}

if (mode_all==4){
     mode_b=.25;
     mode_c=.25;}



float knob_fine = patch.GetAdcValue(CV_2);
     fine_tune = fmap(knob_fine, 0, 10);

    /** Get Coarse, Fine, and V/OCT inputs from hardware 
     *  MIDI Note number are easy to use for defining ranges */


    float cv_voct = patch.GetAdcValue(CV_7);
    float voct    = fmap(cv_voct, 0, 58.9);

    /** Convert from MIDI note number to frequency */
    float midi_nn = fclamp(coarse_tune + fine_tune + voct, 0.f, 127.f);
    float freq_a  = mtof(midi_nn);

    /** Calculate a detune amount */
    float detune_amt1 = patch.GetAdcValue(CV_4);
    float freq_b     = (freq_a + (0.05 * freq_a * detune_amt1))*mode_b;
    float freq_c     = (freq_a - (0.05 * freq_a * detune_amt1))*mode_c;

    float stereoSpread = patch.GetAdcValue(CV_6);
    float spreadBL     = fmap(stereoSpread,0,1);
    float spreadCR     = fmap(stereoSpread,0,1);
    float knob_release = patch.GetAdcValue(CV_8);
    envelope.SetReleaseTime(knob_release);



    /** Set all three oscillators' frequencies */
    osc_a.SetFreq(freq_a);
    osc_b.SetFreq(freq_b);
    osc_c.SetFreq(freq_c);


  // envelope.SetCurve(20);
    
    /** Process each sample of the oscillator and send to the hardware outputs */
    for(size_t i = 0; i < size; i++)
    {
    float env_out=envelope.Process(env_state);
    osc_a.SetAmp(env_out);
    osc_b.SetAmp(env_out);
    osc_c.SetAmp(env_out);
        float sigA = osc_a.Process();
        float sigB = osc_b.Process();
        float sigC = osc_c.Process();

        float sigL = (sigB*spreadBL*.4)+(sigA*.4)+(sigB*.2)+(sigC*.2)-(sigC*spreadBL*.2);
        float sigR = (sigC*spreadCR*.4)+(sigA*.4)+(sigC*.2)+(sigB*.2)-(sigB*spreadCR*.2);
        OUT_L[i]  = sigL;
        OUT_R[i]  = sigR;

        if (wave_ind>1000){
        patch.WriteCvOut(CV_OUT_1, sigL*5);

        }

             if (mode_ind>1000){
        patch.WriteCvOut(CV_OUT_2, sigR*5);}

        }
}

int main(void)
{
    patch.Init();


    button1.Init(patch.D6);
    button2.Init(patch.B10);
    button3.Init(patch.D7);

    envelope.Init(48000);

    // osc_a.SetWaveform(Oscillator::WAVE_POLYBLEP_SAW);
    // osc_b.SetWaveform(Oscillator::WAVE_POLYBLEP_SAW);
    // osc_c.SetWaveform(Oscillator::WAVE_POLYBLEP_SAW);


    osc_a.Init(patch.AudioSampleRate());
    osc_b.Init(patch.AudioSampleRate());
    osc_c.Init(patch.AudioSampleRate());
    
    



    patch.StartAudio(AudioCallback);
    while(1) {}
}
