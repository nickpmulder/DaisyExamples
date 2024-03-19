#include "daisy_patch_sm.h"
#include "daisysp.h"


using namespace daisy;
using namespace daisysp;
using namespace patch_sm;


DaisyPatchSM patch;
ReverbSc     reverb;


void AudioCallback(AudioHandle::InputBuffer  in,
                   AudioHandle::OutputBuffer out,
                   size_t                    size)
{
    patch.ProcessAnalogControls();

    /** Update Params with the four knobs */
    float time_knob = patch.GetAdcValue(CV_8);
    float time      = fmap(time_knob, 0.4, 0.95);

    float damp_knob = patch.GetAdcValue(CV_2);
    float damp      = fmap(damp_knob, 100.f, 19000.f, Mapping::LOG);

    // float crush_knob = patch.GetAdcValue(CV_6);
    // float crushAmount      = fmap(crush_knob, 1, 50);

    float send_level = patch.GetAdcValue(CV_4);

    float in_level = 1-send_level;

    reverb.SetFeedback(time);
    reverb.SetLpFreq(damp);

 //   crush.SetGain(crushAmount);

    for(size_t i = 0; i < size; i++)
    {
        float dryl  = IN_L[i] * in_level;
        float dryr  = IN_R[i] * in_level;
        float sendl = IN_L[i] * send_level;
        float sendr = IN_R[i] * send_level;
        float wetl, wetr;
        float send1l, send1r;



        reverb.Process(sendl, sendr, &wetl, &wetr);
        OUT_L[i] = dryl*0.3 + wetl*0.3;
        OUT_R[i] = dryr*0.3 + wetr*0.3;

        patch.WriteCvOut(CV_OUT_1, wetl*6);
        patch.WriteCvOut(CV_OUT_2, wetr*6);

    }
}


int main(void)
{
    patch.Init();
    reverb.Init(patch.AudioSampleRate());
    patch.StartAudio(AudioCallback);
    while(1) {}
}
