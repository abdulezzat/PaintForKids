#include "AddLineAction.h"
#include "ApplicationManager.h"
#include "GUI\input.h"
#include "GUI\Output.h"
#include "CLine.h"
#include <fstream>

AddLineAction::AddLineAction(ApplicationManager * pApp):Action(pApp)
{}

void AddLineAction::ReadActionParameters() 
{	
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	pOut->PrintMessage("New Line: Click at first corner");
	
	//Read 1st corner and store in point P1
	pIn->GetPointClicked(P1.x, P1.y);

	pOut->PrintMessage("New Line: Click at second corner");

	//Read 2nd corner and store in point P2
	pIn->GetPointClicked(P2.x, P2.y);
	
	if(UI.filled_OR_not) //default is not filled
		RectGfxInfo.isFilled = true;
	else
		RectGfxInfo.isFilled = false;	//get drawing, filling colors and pen width from the interface
	RectGfxInfo.DrawClr = pOut->getCrntDrawColor();
	RectGfxInfo.FillClr = pOut->getCrntFillColor();
	pOut->ClearStatusBar();

}

void AddLineAction::Execute() 
{
	//This action needs to read some parameters first
	ReadActionParameters();
	
	//Create a rectangle with the parameters read from the user
	CLine *R=new CLine(P1, P2, RectGfxInfo);

	//Add the rectangle to the list of figures
	pManager->AddFigure(R);
}

void AddLineAction::Load(ifstream& input) {
	input >> P1.x >> P1.y >> P2.x >> P2.y;
	input >> RectGfxInfo.DrawClr.ucRed >> RectGfxInfo.DrawClr.ucGreen >> RectGfxInfo.DrawClr.ucBlue;
	input >> RectGfxInfo.isFilled;
	if (RectGfxInfo.isFilled) {
		input >> RectGfxInfo.FillClr.ucRed >> RectGfxInfo.FillClr.ucGreen >> RectGfxInfo.FillClr.ucBlue;
	}
	CLine *R = new CLine(P1, P2, RectGfxInfo);
	pManager->AddFigure(R);
}