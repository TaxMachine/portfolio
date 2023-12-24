//
// Created by TaxMachine on 2023-12-24.
//

#include "window.hpp"

#include <chrono>

#include <imgui.h>

#include <emscripten/emscripten.h>

#include "details.hpp"

#include "components/ButtonWithImage.hpp"

using namespace std::chrono;

void createImGUIWindow() {
    ImGui::GetStyle().WindowRounding = 5.0f;
    ImGui::GetStyle().FrameRounding = 10.0f;
    ImGui::GetStyle().FramePadding = ImVec2(5.0f, 5.0f);
    ImGui::GetStyle().ItemSpacing = ImVec2(5.0f, 10.0f);
    ImGui::Begin("Portfolio", nullptr, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoCollapse);
    ImGui::Text("Hello, I am TaxMachine.");

    ImGui::Text("As you can see, I am not a web developer so please do NOT give me a web developer position.");
    ImGui::Text("I am a C++ developer and I am looking for job that uses system languages (excluding Rust).");
    ImGui::Text("But I am not a game developer");

    ImGui::Separator();

    if (ImGui::CollapsingHeader("Languages")) {
        ImGui::Indent();
        for (const auto& [name, start_date] : LANGUAGES) {
            auto now = system_clock::now();
            auto current_year = year_month_day{floor<days>(now)}.year();
            auto duration = current_year - start_date.year();

            ImGui::Text("%s: %d-%d (%d years)", name.c_str(), start_date.year(), start_date.month(), duration.count());
        }
        ImGui::Unindent();
    }

    ImGui::Separator();

    if (ImGui::CollapsingHeader("Social Medias")) {
        ImGui::Indent();
        if (ImGui::Button("Github")) {
            emscripten_run_script("window.open('https://github.com/TaxMachine', '_blank')");
        }
        ImGui::SameLine();
        if (ImGui::Button("Youtube")) {
            emscripten_run_script("window.open('https://www.youtube.com/channel/UCXranBOFFyMLIkhBJv4iaqA', '_blank')");
        }

        ImGui::Unindent();
    }

    ImGui::Separator();

    ImGui::Image((void*)0, ImVec2(0, 0), ImVec2(1, 1), ImVec2(0, 0));

    ImGui::End();
}