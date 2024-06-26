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
    float time      = fmap(time_knob, 0.1f, 1.0f);

    float damp_knob = patch.GetAdcValue(CV_2);
    float damp      = fmap(damp_knob, 1000.f, 19000.f, Mapping::LOG);

    float in_level = patch.GetAdcValue(CV_4);

    float send_level = patch.GetAdcValue(CV_6);

    reverb.SetFeedback(time*1);
    reverb.SetLpFreq(damp);

    for(size_t i = 0; i < size; i++)
    {
        float dryl  = IN_L[i] * in_level;
        float dryr  = IN_R[i] * in_level;
        float sendl = IN_L[i] * send_level;
        float sendr = IN_R[i] * send_level;
        float wetl, wetr;
        reverb.Process(sendl, sendr, &wetl, &wetr);
        OUT_L[i] = dryl + wetl;
        OUT_R[i] = dryr + wetr;

        patch.WriteCvOut(CV_OUT_1, dryl*6);
        patch.WriteCvOut(CV_OUT_2, wetl*6);

    }
}

int main(void)
{
    patch.Init();
    reverb.Init(patch.AudioSampleRate());
    patch.StartAudio(AudioCallback);
    while(1) {}
}
