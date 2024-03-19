#include "daisy_patch_sm.h"
#include "daisysp.h"


using namespace daisy;
using namespace patch_sm;
using namespace daisysp;


DaisyPatchSM patch;
static daisysp::Decimator dec;
float outputL;
float outputR;




void AudioCallback(AudioHandle::InputBuffer  in,
                   AudioHandle::OutputBuffer out,
                   size_t                    size)
{
     patch.ProcessAnalogControls();

     float bitcrushFactor = patch.GetAdcValue(CV_2);

     float downsampleFactor = patch.GetAdcValue(CV_4);

    float bitstoCrushKnob = patch.GetAdcValue(CV_6);
    float bitstoCrush      = fmap(bitstoCrushKnob, 0, 16);

dec.SetBitcrushFactor	(	bitcrushFactor	)	;
dec.SetDownsampleFactor	(	downsampleFactor	)	;
dec.SetBitsToCrush	(	bitstoCrush	)	;

    for(size_t i = 0; i < size; i++)
    {


        float inputL=  in[0][i];
        float inputR=  in[1][i];
        
        outputL = dec.Process(inputL);
        outputR = dec.Process(inputR);


        out[0][i] = outputL; 
        out[1][i] = outputR; 
    }
}

int main(void)
{
    patch.Init();

    patch.StartAudio(AudioCallback);
    while(1) {}
}
