#include "EventPropogationMixin.h"

using namespace Alice::Core;

void EventPropogationMixin::postEventToChildren(wxEvent &event, wxWindow *parent)
{
    if (!parent)
    {
        parent = wxTheApp->GetTopWindow();
    }

    wxWindowList &children = parent->GetChildren();
    for (wxWindowList::iterator it = children.begin(); it != children.end(); ++it)
    {
        wxWindow *child = *it;
        wxPostEvent(child, event);
        // Recursive call to ensure all descendants receive the event
        postEventToChildren(event, child);
    }
}

void EventPropogationMixin::queueEventToChildren(wxEvent &event, wxWindow *parent)
{
    if (!parent)
    {
        parent = wxTheApp->GetTopWindow();
    }

    wxWindowList &children = parent->GetChildren();
    for (wxWindowList::iterator it = children.begin(); it != children.end(); ++it)
    {
        wxWindow *child = *it;
        wxQueueEvent(child, event.Clone());
        // Recursive call to ensure all descendants receive the event
        queueEventToChildren(event, child);
    }
}