#include "daisy_patch_sm.h"
#include "daisysp.h"

using namespace daisy;
using namespace patch_sm;
using namespace daisysp;

DaisyPatchSM patch;
Switch       button1;
Switch       button2;

#define kBuffSize 48000 * 60 // 60 seconds at 48kHz

// Loopers and the buffers they'll use
Looper              looper_l;
Looper              looper_r;
float DSY_SDRAM_BSS buffer_l[kBuffSize];
float DSY_SDRAM_BSS buffer_r[kBuffSize];

void AudioCallback(AudioHandle::InputBuffer  in,
                   AudioHandle::OutputBuffer out,
                   size_t                    size)
{
    // Process the controls
    patch.ProcessAllControls();
    button1.Debounce();
    button2.Debounce();

    // Set in and loop gain from CV_1 and CV_2 respectively
    float in_level   = patch.GetAdcValue(CV_2);
    float loop_level = patch.GetAdcValue(CV_4);

    //if you press the button, toggle the record state
    if(button1.RisingEdge()|| button2.RisingEdge())
    {
        looper_l.TrigRecord();
        looper_r.TrigRecord();
    }


    // if you hold the button longer than 1000 ms (1 sec), clear the loop
    if(button1.TimeHeldMs() >= 1000.f)
    {
        looper_l.Clear();
        looper_r.Clear();
    }

    // Set the led to 5V if the looper is recording
    patch.WriteCvOut(2, 5.f * looper_l.Recording());

    // Process audio
    for(size_t i = 0; i < size; i++)
    {
        // store the inputs * the input gain factor
        float in_l = IN_L[i] * in_level;
        float in_r = IN_R[i] * in_level;

        // store signal = loop signal * loop gain + in * in_gain
        float sig_l = looper_l.Process(in_l) * loop_level + in_l;
        float sig_r = looper_r.Process(in_r) * loop_level + in_r;

        // send that signal to the outputs
        OUT_L[i] = sig_l;
        OUT_R[i] = sig_r;
    }
}

int main(void)
{
    // Initialize the hardware
    patch.Init();

    // Init the loopers
    looper_l.Init(buffer_l, kBuffSize);
    looper_r.Init(buffer_r, kBuffSize);

    // Init the button
    button1.Init(patch.D6);
    button2.Init(patch.B10);

    // Start the audio callback
    patch.StartAudio(AudioCallback);

    // loop forever
    while(1) {}
}
