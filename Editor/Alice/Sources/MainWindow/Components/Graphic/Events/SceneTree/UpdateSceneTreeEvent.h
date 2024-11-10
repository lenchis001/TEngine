#ifndef ALICE_UPDATE_SCENE_TREE_EVENT_H
#define ALICE_UPDATE_SCENE_TREE_EVENT_H

#include <vector>
#include <memory>

#include "wx/wxprec.h"

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include "IEngine.h"

#include "SceneTreeItem.h"

using namespace TEngine::Components::Graphics::Rendering::Scene::RenderingStrategies;

namespace Alice::MainWindow::Components::Graphic::Events::SceneTree
{
    class UpdateSceneTreeEvent : public wxEvent
    {
    public:
        UpdateSceneTreeEvent(const SceneTreeItem &item);

        UpdateSceneTreeEvent();

        const SceneTreeItem &getItem() const;

        wxEvent *Clone() const override;

        static UpdateSceneTreeEvent fromRenderingStrategy(std::shared_ptr<IRenderingStrategy> renderingStrategy);

    private:
        static SceneTreeItem toSceneTree(std::shared_ptr<IRenderingStrategy> renderingStrategy);

        SceneTreeItem _item;
    };

    wxDECLARE_EVENT(UPDATE_SCENE_TREE_EVENT_TYPE, UpdateSceneTreeEvent);

    typedef void (wxEvtHandler::*UpdateSceneTreeEventFunction)(UpdateSceneTreeEvent &);
#define UpdateSceneTreeEventHandler(func) wxEVENT_HANDLER_CAST(UpdateSceneTreeEventFunction, func)

#define EVT_UPDATE_SCENE_TREE(func) wx__DECLARE_EVT1(UPDATE_SCENE_TREE_EVENT_TYPE, wxID_ANY, UpdateSceneTreeEventFunction(func))
}

#endif // ALICE_UPDATE_SCENE_TREE_EVENT_H