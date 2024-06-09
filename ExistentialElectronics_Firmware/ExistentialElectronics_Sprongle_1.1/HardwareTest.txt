//SPRONGLE 1.1 2024.05.07 ExistentialElectronics


#include "daisy_patch_sm.h"
#include "daisysp.h"



using namespace daisy;
using namespace patch_sm;
using namespace daisysp;

DaisyPatchSM patch;
Oscillator   osc_a, osc_b, osc_c, osc_d, osc_e, osc_f, osc_g;
Wavefolder fold;
Overdrive drive;
Adsr envelope;
Switch button1;
Switch button2;
Switch button3;
Switch button4;
Switch button5;
float volume = 1;
float coarse_tune =0;
float calibrate =0;
float fine_tune =0;
float lin_tune=0;
float waveForm=1;
int mode_all=1;
int wave_ind = 0;
float mode_b=1;
float mode_c=1;
int mode_ind=0;
float detuneLast=0;
void AudioCallback(AudioHandle::InputBuffer  in,
                   AudioHandle::OutputBuffer out,
                   size_t                    size)
{
    patch.ProcessAllControls();
    button1.Debounce();
    button2.Debounce();
    button3.Debounce();
    button4.Debounce();
    button5.Debounce();


        bool env_state;

wave_ind++;
mode_ind++;









if(button1.RisingEdge()  ){
    
    waveForm=waveForm+1;
    if (waveForm==6){waveForm=1;}

    wave_ind=0;


}


  
    if (waveForm == 1){


    osc_a.SetWaveform(Oscillator::WAVE_SQUARE);
    osc_b.SetWaveform(Oscillator::WAVE_SQUARE);
    osc_c.SetWaveform(Oscillator::WAVE_SQUARE);
    osc_d.SetWaveform(Oscillator::WAVE_SQUARE);
    osc_e.SetWaveform(Oscillator::WAVE_SQUARE);
    osc_f.SetWaveform(Oscillator::WAVE_SQUARE);
    osc_g.SetWaveform(Oscillator::WAVE_SQUARE);


               // fold.SetGain(1);
                drive.SetDrive(0.3);
                volume=2;
    if (wave_ind == 100){ patch.WriteCvOut(CV_OUT_1, 5);}
    if (wave_ind == 200){ patch.WriteCvOut(CV_OUT_1, 0);}

        }




    if (waveForm == 2){
    osc_a.SetWaveform(Oscillator::WAVE_POLYBLEP_SAW);
    osc_b.SetWaveform(Oscillator::WAVE_POLYBLEP_SAW);
    osc_c.SetWaveform(Oscillator::WAVE_POLYBLEP_SAW);
    osc_d.SetWaveform(Oscillator::WAVE_POLYBLEP_SAW);
    osc_e.SetWaveform(Oscillator::WAVE_POLYBLEP_SAW);
    osc_f.SetWaveform(Oscillator::WAVE_POLYBLEP_SAW);
    osc_g.SetWaveform(Oscillator::WAVE_POLYBLEP_SAW);
               // fold.SetGain(1);
                drive.SetDrive(0.3);
                volume=2;

      
    if (wave_ind == 100){ patch.WriteCvOut(CV_OUT_1, 5);}
    if (wave_ind == 200){ patch.WriteCvOut(CV_OUT_1, 0);}

    if (wave_ind == 300){ patch.WriteCvOut(CV_OUT_1, 5);}
    if (wave_ind == 400){ patch.WriteCvOut(CV_OUT_1, 0);} 

        }

    if (waveForm == 3){
   

    osc_a.SetWaveform(Oscillator::WAVE_POLYBLEP_SAW);
    osc_b.SetWaveform(Oscillator::WAVE_POLYBLEP_SAW);
    osc_c.SetWaveform(Oscillator::WAVE_POLYBLEP_SAW);
    osc_d.SetWaveform(Oscillator::WAVE_POLYBLEP_SAW);
    osc_e.SetWaveform(Oscillator::WAVE_POLYBLEP_SAW);
    osc_f.SetWaveform(Oscillator::WAVE_SQUARE);
    osc_g.SetWaveform(Oscillator::WAVE_SQUARE);
           // fold.SetGain(1);
            drive.SetDrive(0.4);
                volume=1.5;

    
    
    if (wave_ind == 100){ patch.WriteCvOut(CV_OUT_1, 5);}
    if (wave_ind == 200){ patch.WriteCvOut(CV_OUT_1, 0);}

    if (wave_ind == 300){ patch.WriteCvOut(CV_OUT_1, 5);}
    if (wave_ind == 400){ patch.WriteCvOut(CV_OUT_1, 0);}  

    if (wave_ind == 500){ patch.WriteCvOut(CV_OUT_1, 5);}
    if (wave_ind == 600){ patch.WriteCvOut(CV_OUT_1, 0);} 



        }

    if (waveForm == 4){


    osc_a.SetWaveform(Oscillator::WAVE_POLYBLEP_SAW);
    osc_b.SetWaveform(Oscillator::WAVE_POLYBLEP_SAW);
    osc_c.SetWaveform(Oscillator::WAVE_POLYBLEP_SAW);
    osc_d.SetWaveform(Oscillator::WAVE_SQUARE);
    osc_e.SetWaveform(Oscillator::WAVE_SQUARE);
    osc_f.SetWaveform(Oscillator::WAVE_POLYBLEP_SAW);
    osc_g.SetWaveform(Oscillator::WAVE_POLYBLEP_SAW);
           // fold.SetGain(1);
            drive.SetDrive(.6);
                volume=1;



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

    osc_a.SetWaveform(Oscillator::WAVE_POLYBLEP_SAW);
    osc_b.SetWaveform(Oscillator::WAVE_POLYBLEP_SAW);
    osc_c.SetWaveform(Oscillator::WAVE_POLYBLEP_SAW);
    osc_d.SetWaveform(Oscillator::WAVE_POLYBLEP_SAW);
    osc_e.SetWaveform(Oscillator::WAVE_POLYBLEP_SAW);
    osc_f.SetWaveform(Oscillator::WAVE_POLYBLEP_SAW);
    osc_g.SetWaveform(Oscillator::WAVE_POLYBLEP_SAW);
        fold.SetGain(6);
        drive.SetDrive(.9);    
                    volume=1;

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





 if(button2.Pressed())
        env_state = true;
    else
        env_state = false;
 



 if(button3.RisingEdge() ){
    
    mode_all=mode_all+1;
    if (mode_all==5){mode_all=1;}
    mode_ind=0;

}






//mode settings


//octave regular
if (mode_all==1){
     mode_b=1;
     mode_c=1;
     if (mode_ind == 100){ patch.WriteCvOut(CV_OUT_2, 5);}
if (mode_ind == 200){ patch.WriteCvOut(CV_OUT_2, 0);}}


//regular plus octave up
if (mode_all==2){
     mode_b=2;
     mode_c=2;
     if (mode_ind == 100){ patch.WriteCvOut(CV_OUT_2, 5);}
if (mode_ind == 200){ patch.WriteCvOut(CV_OUT_2, 0);}

 if (mode_ind == 300){ patch.WriteCvOut(CV_OUT_2, 5);}
if (mode_ind == 400){ patch.WriteCvOut(CV_OUT_2, 0);}   }


//regular plus octave down
if (mode_all==3){
     mode_b=.5;
     mode_c=.5;
         
if (mode_ind == 100){ patch.WriteCvOut(CV_OUT_2, 5);}
if (mode_ind == 200){ patch.WriteCvOut(CV_OUT_2, 0);}

 if (mode_ind == 300){ patch.WriteCvOut(CV_OUT_2, 5);}
if (mode_ind == 400){ patch.WriteCvOut(CV_OUT_2, 0);}  

 if (mode_ind == 500){ patch.WriteCvOut(CV_OUT_2, 5);}
if (mode_ind == 600){ patch.WriteCvOut(CV_OUT_2, 0);} }


//regular plus fifth
if (mode_all==4){
     mode_b=1.5;
     mode_c=1.5;
         
if (mode_ind == 100){ patch.WriteCvOut(CV_OUT_2, 5);}
if (mode_ind == 200){ patch.WriteCvOut(CV_OUT_2, 0);}

 if (mode_ind == 300){ patch.WriteCvOut(CV_OUT_2, 5);}
if (mode_ind == 400){ patch.WriteCvOut(CV_OUT_2, 0);}  

 if (mode_ind == 500){ patch.WriteCvOut(CV_OUT_2, 5);}
if (mode_ind == 600){ patch.WriteCvOut(CV_OUT_2, 0);} 


 if (mode_ind == 700){ patch.WriteCvOut(CV_OUT_2, 5);}
if (mode_ind == 800){ patch.WriteCvOut(CV_OUT_2, 0);} }



float knob_fine = patch.GetAdcValue(CV_1);
     fine_tune = fmap(knob_fine, 0, 20);



float knob_coarse = patch.GetAdcValue(CV_5);
     coarse_tune = fmap(knob_coarse, 0, 200);



float knob_calibrate = patch.GetAdcValue(CV_6);
     calibrate = fmap(knob_calibrate, 0, 30);


float cv_voct = patch.GetAdcValue(CV_8);
    float voct    = fmap(cv_voct, 0,160+calibrate);

    /** Convert from MIDI note number to frequency */
    float midi_nn = fclamp(coarse_tune + fine_tune + voct, 0.f, 127.f);
    float freq_a  = mtof(midi_nn);

    /** Calculate a detune amount */
    float detune_amt1 = patch.GetAdcValue(CV_3)/2;
    float freq_b     = (freq_a + (0.1 * freq_a * (detune_amt1*.4)))*mode_b;
    float freq_c     = (freq_a - (0.1 * freq_a * (detune_amt1*.5)))*mode_c;
    float freq_d     = (freq_a + (0.1 * freq_a * (detune_amt1*.7)));
    float freq_e     = (freq_a - (0.1 * freq_a * (detune_amt1*1.0)));
    float freq_f     = (freq_a + (0.1 * freq_a * (detune_amt1*1.2)))*mode_b;
    float freq_g     = (freq_a - (0.1 * freq_a * (detune_amt1*1.4)))*mode_c;

    float stereoSpread = patch.GetAdcValue(CV_2);
    float spread     = fmap(stereoSpread,0,1);

    float knob_release = patch.GetAdcValue(CV_4);
    envelope.SetReleaseTime(knob_release);



    /** Set all three oscillators' frequencies */
    osc_a.SetFreq(freq_a);
    osc_b.SetFreq(freq_b);
    osc_c.SetFreq(freq_c);
    osc_d.SetFreq(freq_d);
    osc_e.SetFreq(freq_e);
    osc_f.SetFreq(freq_f);
    osc_g.SetFreq(freq_g);


    
    /** Process each sample of the oscillator and send to the hardware outputs */
    for(size_t i = 0; i < size; i++)
    {
    float env_out=envelope.Process(env_state);


        float sigA = osc_a.Process();
        float sigB = osc_b.Process();
        float sigC = osc_c.Process();
        float sigD = osc_d.Process();
        float sigE = osc_e.Process();
        float sigF = osc_f.Process();
        float sigG = osc_g.Process();

        float send1L = (sigB*spread*.2)+(sigD*spread*.2)+(sigF*spread*.1)+
                                
                                (sigA*.2)+(sigB*.2)+(sigC*.2)+(sigD*.2)+(sigE*.2)+(sigF*.1)+(sigG*.1)-
                                
                                        (sigC*spread*.2)-(sigE*spread*.2)-(sigG*spread*.1);
        
        
        float send1R = (sigC*spread*.2)+(sigE*spread*.2)+(sigG*spread*.1)+
                            
                                (sigA*.2)+(sigB*.2)+(sigC*.2)+(sigD*.2)+(sigE*.2)+(sigF*.1)+(sigG*.1)-
                                
                                        (sigB*spread*.2)-(sigD*spread*.2)-(sigF*spread*.1);
       
    
             
        float sigL= drive.Process(send1L)*env_out*volume;
        float sigR= drive.Process(send1R)*env_out*volume;
       



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
    button4.Init(patch.D4);
    button5.Init(patch.D5);

    envelope.Init(48000);




    osc_a.Init(patch.AudioSampleRate());
    osc_b.Init(patch.AudioSampleRate());
    osc_c.Init(patch.AudioSampleRate());
    osc_d.Init(patch.AudioSampleRate());
    osc_e.Init(patch.AudioSampleRate());
    osc_f.Init(patch.AudioSampleRate());
    osc_g.Init(patch.AudioSampleRate());
       
    



    patch.StartAudio(AudioCallback);
    while(1) {}
}
