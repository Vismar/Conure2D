#pragma once

namespace Renderer
{
    /*!
     * \brief Public interface for render system that should be used by game logic.
     */
    class RenderSystemInterface
    {
    public:
        RenderSystemInterface(const RenderSystemInterface& other) = delete;
        RenderSystemInterface(RenderSystemInterface&& other) = delete;
        RenderSystemInterface& operator=(const RenderSystemInterface& other) = delete;
        RenderSystemInterface& operator=(RenderSystemInterface&& other) = delete;
        RenderSystemInterface() = default;
        virtual ~RenderSystemInterface() = default;
    };
}