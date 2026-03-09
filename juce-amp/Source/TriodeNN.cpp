#include "TriodeNN.h"
#include <BinaryData.h>
#include "tensorflow/c/c_api.h"
#include <windows.h>


TriodeNN::TriodeNN()
{  
}
void printTensorflowDllPath()
{
    HMODULE hModule = GetModuleHandleA("tensorflow.dll");

    if (hModule != nullptr)
    {
        char path[MAX_PATH];
        GetModuleFileNameA(hModule, path, MAX_PATH);

        juce::Logger::writeToLog("TensorFlow DLL carregada de: " + juce::String(path));
    }
    else
    {
        juce::Logger::writeToLog("tensorflow.dll NAO carregada");
    }
}
void TriodeNN::prepare()
{
    printTensorflowDllPath();

    try {
        if (!triodeModel)
            juce::Logger::writeToLog("VERSÂO TF: " + juce::String(TF_Version()));
            triodeModel = std::make_unique<cppflow::model>("C:/AudioPlugins/Models/triode_model");
    }
    catch (const std::exception& e) {
		juce::Logger::writeToLog("VERSÂO TF: " + juce::String(TF_Version()));   
        juce::Logger::writeToLog("Erro ao carregar modelo: " + juce::String(e.what()));
        int breakpoint = 0;
    }
}

float TriodeNN::process(float vgk) 
{
    if (!triodeModel) {
        if (notLogged)
        {
            juce::Logger::writeToLog("TRIODO NAO INICIADO");
            return vgk;
            notLogged = false;
        }
    }
    try {
        if (notLogged)
        {
            juce::Logger::writeToLog("TRIODO INICIADO CORRETAMENTE ");
            notLogged = false;
        }
        std::vector<float> data = { vgk };
        std::vector<int64_t> shape = { 1, 1 };
        cppflow::tensor input(data, shape);

        auto output = (*triodeModel)(input);

        
        return output.get_data<float>()[0];
    }

    catch (const std::exception& e) {
        auto ops = triodeModel->get_operations(); 
        for (auto& op : ops) {
        juce::Logger::writeToLog("Operacao encontrada: " + juce::String(op.c_str()));
        return vgk;
        }
        juce::Logger::writeToLog("Erro ao executar o modelo: " + juce::String(e.what()));
        int breakpoint = 0;
        return vgk;
    }
}
