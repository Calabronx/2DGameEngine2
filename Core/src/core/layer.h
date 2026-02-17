#pragma once
#ifndef LAYER_H
#define LAYER_H

#include "event.h"

namespace Engine {

	class Layer
	{
		public:
			virtual ~Layer() = default;

			virtual void OnEvent(Event& event) {}

			virtual void OnUpdate(float ts) {}
			virtual void OnRender() {}
	};
}

#endif
