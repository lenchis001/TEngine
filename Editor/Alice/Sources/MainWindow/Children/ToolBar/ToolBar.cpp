#include "ToolBar.h"

#include "wx/dcsvg.h"

using namespace Alice::MainWindow::Children::ToolBar;

#define TOOL_SIZE 32

ToolBar::ToolBar(wxWindow *parent) : IToolBar(parent)
{
    SetMargins(4, 4);

    auto bgColor = wxColour(0xF5, 0xF5, 0xF5);

    SetBackgroundColour(bgColor);

    AddTool(wxID_ANY, "Select", _createColoredBitmap("./AliceResources/Controls/Select.svg", wxSize(TOOL_SIZE, TOOL_SIZE), bgColor));
    AddTool(wxID_ANY, "Move", _createColoredBitmap("./AliceResources/Controls/Move.svg", wxSize(TOOL_SIZE, TOOL_SIZE), bgColor));
    AddTool(wxID_ANY, "Rotate", _createColoredBitmap("./AliceResources/Controls/Rotate.svg", wxSize(TOOL_SIZE, TOOL_SIZE), bgColor));

    Realize();
}

wxBitmap ToolBar::_createColoredBitmap(const wxString &filePath, const wxSize &size, const wxColour &bgColor)
{
    // Create a bitmap with the desired background color
    wxBitmap bitmap(size);
    wxMemoryDC dc(bitmap);
    dc.SetBackground(wxBrush(bgColor));
    dc.Clear();

    // Load the SVG icon
    wxBitmapBundle bundle = wxBitmapBundle::FromSVGFile(filePath, size);
    if (!bundle.IsOk())
    {
        wxLogError("Failed to load SVG file: %s", filePath);
        return wxBitmap();
    }

    // Draw the SVG icon on the custom bitmap
    wxBitmap svgBitmap = bundle.GetBitmap(size);
    dc.DrawBitmap(svgBitmap, 0, 0, true);

    return bitmap;
}