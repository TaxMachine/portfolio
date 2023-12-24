//
// Created by TaxMachine on 2023-12-24.
//

#ifndef BUTTONWITHIMAGE_HPP
#define BUTTONWITHIMAGE_HPP

#include <string>

#include <imgui.h>

#include "../utils/image.hpp"

namespace ImGui {
    inline bool ButtonWithImage(const char* label, const char* image, const ImVec2& size = ImVec2(0, 0)) {
        GLuint texture_id;
        int width, height;
        if (!LoadTextureFromFile(image, &texture_id, &width, &height)) {
            return false;
        }

        ImGui::PushID(label);
        ImGui::BeginGroup();
        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0, 0, 0, 0));
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0, 0, 0, 0));
        const bool clicked = ImGui::ImageButton((void*)(intptr_t)texture_id, size);
        ImGui::PopStyleColor(3);
        ImGui::EndGroup();
        ImGui::SameLine();
        ImGui::Text(label);
        ImGui::PopID();

        return clicked;
    }
}

#endif //BUTTONWITHIMAGE_HPP
