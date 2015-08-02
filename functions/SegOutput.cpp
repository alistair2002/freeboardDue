#include "SegOutput.h"

SegOutput::SegOutput():choice(SEG_OUTPUT_MAG) {
	this->model = model;
}

SegOutput::~SegOutput() {}

void SegOutput::choose(int output)
{
	switch (output)
	{
		case 1:
			choice = SEG_OUTPUT_MAG;
			break;
		default:
			choice = SEG_OUTPUT_NONE;
			break;
	}
}
void SegOutput::tick()
{
	switch( choice )
	{
		case SEG_OUTPUT_MAG:
		{
			/* things that need tickling alot to keep happy */
			HDM_T *magnetic_heading = model->get_HDM();
	
			/* this is a raster display so needs refreshing, makes a cool watchdog */
			seg_disp.tick_event((int)magnetic_heading->heading);
			break;
		}
		case SEG_OUTPUT_COG:
		{
			RMC_T *gps = model->get_RMC(); /* recommended minimum */
			seg_disp.tick_event((int)gps->dir);
			break;
		}
		case SEG_OUTPUT_NONE:
		default:
			break;
	}
}
