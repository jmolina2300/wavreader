//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "frmMain.h"
#include "wavread.h"


#define PLOT_SCALE 2000

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button1Click(TObject *Sender)
{
    bool success = OpenDialog1->Execute();
    if (!success) {
        return;
    }
    tbxFileName->Text = OpenDialog1->FileName;

    // Clear the chart and info box
    DBChart1->Series[0]->Clear();
    tbxFileInfo->Clear();

    // Get information about the WAV file
    WaveInfo wi;
    FILE *infile = fopen(tbxFileName->Text.c_str(), "rb");
    if (infile == NULL) {
        MessageBox(NULL, "Cannot open that file!", "Error", MB_OK);
        return;
    }
    bool acceptableFile = read_pcm_wav_info(infile, tbxFileName->Text.c_str(), &wi);
    if (acceptableFile) {
		AnsiString fileInfo;
		fileInfo.printf("        Name: %s\n"
						"        Bits: %d\n"
						" Sample Rate: %d\n"
						"    Channels: %d\n"
						"    Duration: %.2lf\n"
						"     Samples: %d\n",
						ExtractFileName(OpenDialog1->FileName),
						wi.BitsPerSample,
						wi.SampleRate,
						wi.NumChannels,
						wi.Duration,
						wi.NumSamples);
        tbxFileInfo->Text = fileInfo;
    } else {
        MessageBox(NULL, "Unsupported WAV format!", "Error", MB_OK);
        fclose(infile);
        return;
    }
	
	/* At this point, the file pointer has been moved up to the data portion.
	 * So we can proceed to read the samples.
     */

    DBChart1->Series[0]->Clear();


    // Create buffer for the audio data
    size_t audio_window_ms = AUDIO_WINDOW_MS;
    size_t buffer_samples = wi.SampleRate * (audio_window_ms / 1000.0);
    int16_t *inbuffer = (int16_t*)malloc(buffer_samples * wi.BlockAlign);

    size_t  numSamplesTotal = 0;
    size_t  numSamplesRead = 0;
    TChartSeries* tmpSeries = (TChartSeries*)DBChart1->Series[0];

    // Represent a waveform of arbitrary length using a 2000-element array
    int16_t  valuesToPlot[PLOT_SCALE];
    size_t  valuesToPlotIndex = 0;
    size_t  delta = wi.NumSamples / PLOT_SCALE;
    size_t  deltaCounter = 0;
    do {
        
        numSamplesRead = fread(inbuffer, wi.BlockAlign, buffer_samples, infile);

        /* Add the values to the array using the delta value to tell when
         *   to actually add each one.
         */
        for (size_t i = 0; i < numSamplesRead; i++) {
            int16_t sample_amplitude = inbuffer[i];
            if (deltaCounter == delta) {
                valuesToPlot[valuesToPlotIndex] = sample_amplitude;
                valuesToPlotIndex++;
                deltaCounter = 0;
            }
            deltaCounter++;
        }
        numSamplesTotal += numSamplesRead;
    } while (numSamplesRead != 0) ;


    // Finally, add the values to the chart 
    for (size_t i = 0; i < PLOT_SCALE; i++)
        tmpSeries->AddXY(i, valuesToPlot[i]);

    DBChart1->RefreshData();
    
    
    free (inbuffer);
    fclose (infile);    
}
//---------------------------------------------------------------------------


