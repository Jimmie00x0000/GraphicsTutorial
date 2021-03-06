#pragma once
#include "scene.h"
#include "renderer.h"

namespace zjl {
static bool			is_rotating_view = false;
static bool			is_models_widget_collapsing = false;
static Scene		scene;
static Renderer		renderer;
static double		xpos, ypos;
static const int	default_viewport_width = 1200;
static const int	default_viewport_height = 800;
static const int	toolset_region_width = 250;
static int			current_viewport_width = default_viewport_width;
static int			current_viewport_height = default_viewport_height;
static std::string  current_working_directory;
static float		frame_time = 0.0;
static bool			auto_resize = true;
static int			selected_model_index = -1;


int ShowWindow();

}


