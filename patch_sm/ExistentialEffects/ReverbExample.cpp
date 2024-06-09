#include "daisy_patch_sm.h"
#include "daisysp.h"


using namespace daisy;
using namespace daisysp;
using namespace patch_sm;


DaisyPatchSM patch;
Overdrive drive;
Wavefolder fold;
Decimator decimator;
//Svf svf1, svf2;

void AudioCallback(AudioHandle::InputBuffer  in,
                   AudioHandle::OutputBuffer out,
                   size_t                    size)
{
    patch.ProcessAnalogControls();

    /** Update Params with the four knobs */


    float drive_knob = patch.GetAdcValue(CV_8);
    float driveAmount      = fmap(drive_knob, 0.25, 1);

    float downsample_knob = patch.GetAdcValue(CV_2);
    float downsampleAmount      = fmap(downsample_knob, 0, 3);

    float crush_knob = patch.GetAdcValue(CV_4);
    float crushAmount      = fmap(crush_knob, 0, 1);

    float fold_knob = patch.GetAdcValue(CV_6);
    float foldAmount      = fmap(fold_knob, 1, 20);

   // float send_level = patch.GetAdcValue(CV_4);
  //  decimator.SetBitcrushFactor(crushAmount);
    decimator.SetDownsampleFactor(downsampleAmount);
    drive.SetDrive(driveAmount);
    fold.SetGain(foldAmount);

    // svf1.SetFreq(freqAmount);
    // svf1.SetRes(resAmount);

    // svf2.SetFreq(freqAmount);
    // svf2.SetRes(resAmount);


    for(size_t i = 0; i < size; i++)
    {


        float send1L= fold.Process(IN_L[i]);
        float send1R= fold.Process(IN_R[i]);

        float send2L= drive.Process(send1L);
        float send2R= drive.Process(send1R);

        float send3L= decimator.Process(send2L);
        float send3R= decimator.Process(send2R);

        // float send3L= svf1.Low();;
        // float send3R= svf2.Low();;


        OUT_L[i] = send3L;
        OUT_R[i] = send3R;

        patch.WriteCvOut(CV_OUT_1, send3L*6);
        patch.WriteCvOut(CV_OUT_2, send3R*6);

    }
}


int main(void)
{

        float samplerate;

    patch.Init();

    samplerate = patch.AudioSampleRate();

    //Initialize filter
    // svf1.Init(samplerate);
    // svf2.Init(samplerate);

    patch.StartAudio(AudioCallback);
    while(1) {}
}
