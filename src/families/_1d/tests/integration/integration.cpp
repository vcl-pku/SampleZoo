/*
FILE: integration.cpp
AUTHOR: Alan Wolfe (alan.wolfe@gmail.com)
DATE: 2/13/2019

Description:
Uses samples to integrate 1d functions
*/

#include "codegen.h"
#include "shared/math.h"
#include "shared/graph.h"

static const float e = 2.71828182845904523536f;

static float Linear(float x)
{
    // function:  y = x
    return x;
}

static float Step(float x)
{
    // function:  y = (x > 0.5) ? 1 : 0
    return x > 0.5f ? 1.0f : 0.0f;
}

static float Exp(float x)
{
    // function:  y = e^x
    return expf(x);
}

static float Quadratic(float x)
{
    // function: y = 3x^2+2x+1
    return 3.0f*x*x + 2.0f*x + 1.0f;
}

template <typename LAMBDA>
static void GetErrorData(const std::vector<float>& samples, GraphItem& error, const LAMBDA& lambda, const float c_actual)
{
    error.data.resize(samples.size());
    float approximation = 0.0f;
    for (size_t index = 0, count = samples.size(); index < count; ++index)
    {
        float y = lambda(samples[index]);
        approximation = Lerp(approximation, y, 1.0f / float(index + 1));
        error.data[index][0] = float(index + 1);
        error.data[index][1] = fabsf(c_actual - approximation) / c_actual;
    }
}

template <typename LAMBDA>
static void DoIntegrationTest(const std::vector<std::vector<SampleGenerateInfo_1d>>& sampleFunctions, const char* testName, const char* fileNamePrefix, const LAMBDA& lambda, const float c_actual)
{
    static const size_t sampleCount = 4096;
    char buffer[256];

    for (const std::vector<SampleGenerateInfo_1d>& sampleType : sampleFunctions)
    {
        if (sampleType.size() == 0)
            continue;

        GraphDesc desc;

        // useful for log graphs
        //put x axis ticks at every power of 10
        int i = 1;
        while (i <= sampleCount)
        {
            sprintf(buffer, "%i", i);
            desc.xAxisTicks.push_back(GraphAxisTick{ float(i), buffer, TextHAlign::Right, TextVAlign::Top });
            i *= 10;
        }

        sprintf(buffer, "%zu", sampleCount);
        desc.xAxisTicks.push_back(GraphAxisTick{ float(sampleCount), buffer, TextHAlign::Right, TextVAlign::Top });

        // useful for non log graphs
        /*
        std::vector<GraphAxisTick> xAxisTicks;
        static int c_numXAxisTicks = 11;
        for (int i = 0; i < c_numXAxisTicks; ++i)
        {
            int count = int(float(sampleCount) *  (float(i) / float(c_numXAxisTicks - 1)));
            if (i == 0)
                count = 1;

            char buffer[256];
            sprintf(buffer, "%i", count);
            xAxisTicks.push_back({ float(count), buffer, TextHAlign::Right, TextVAlign::Top });
        }
        */

        char fileName[256];
        float globalminy = FLT_MAX;
        float globalmaxy = -FLT_MAX;
        for (const SampleGenerateInfo_1d& sampleFunction : sampleType)
        {
            std::vector<float> samples;
            sampleFunction.function(samples, sampleCount, sampleFunction.cacheKey, false);
            sprintf(fileName, "output/%s/samples/%s/%s%s_%s.png", sampleFunction.sampleFamily, sampleFunction.sampleType, fileNamePrefix, testName, sampleFunction.name);

            desc.graphItems.resize(desc.graphItems.size() + 1);
            GraphItem& error = *desc.graphItems.rbegin();
            error.label = sampleFunction.name;
            GetErrorData(samples, error, lambda, c_actual);

            // put y axis ticks at the min and max y
            std::vector<GraphAxisTick> yAxisTicks;
            float miny = FLT_MAX;
            float maxy = -FLT_MAX;
            for (Vec2& v : error.data)
            {
                miny = std::min(miny, v[1]);
                maxy = std::max(maxy, v[1]);
            }
            sprintf(buffer, "%0.2f", miny);
            yAxisTicks.push_back({ miny, buffer, TextHAlign::Right, TextVAlign::Top });
            sprintf(buffer, "%0.2f", maxy);
            yAxisTicks.push_back({ maxy, buffer, TextHAlign::Right, TextVAlign::Top });
            globalminy = std::min(globalminy, miny);
            globalmaxy = std::max(globalmaxy, maxy);

            // make the individual graph
            std::vector<GraphItem> graph;
            graph.push_back(error);
            // don't make the individual graphs. they aren't useful
            //MakeGraph(fileName, graph, xAxisTicks, yAxisTicks, 512, false, { 0.0f, 0.0f }, { 0.01f, 0.01f });
        }

        float value = 1.0f;
        for (int i = 1; i <= 7; ++i)
        {
            sprintf(buffer, "10^-%i", i);
            desc.yAxisTicks.push_back({ value, buffer, TextHAlign::Right, TextVAlign::Top });
            value /= 10.0f;
        }

        // make the sample type graph
        sprintf(fileName, "output/%s/samples/%s/%s%s.png", sampleType[0].sampleFamily, sampleType[0].sampleType, fileNamePrefix, testName);
        sprintf(buffer, "Numerical Integration: %s function", testName);

        desc.graphType = GraphType::Points;
        desc.fileName = fileName;
        desc.title = buffer;
        desc.footer = "x axis is sample count, y axis is percent error. Graph is log/log.";
        desc.loglog = true;
        desc.forceYMinMax = true;
        desc.yMinMax = Vec2{ 0.0f, 1.0f };
        MakeGraph(desc);
    }
}

void _1d::Tests::Integration::Linear(const std::vector<std::vector<SampleGenerateInfo_1d>>& sampleFunctions, const char* testName, const char* fileNamePrefix)
{
    DoIntegrationTest(sampleFunctions, testName, fileNamePrefix, ::Linear, 0.5f);
}

void _1d::Tests::Integration::Step(const std::vector<std::vector<SampleGenerateInfo_1d>>& sampleFunctions, const char* testName, const char* fileNamePrefix)
{
    DoIntegrationTest(sampleFunctions, testName, fileNamePrefix, ::Step, 0.5f);
}

void _1d::Tests::Integration::Exp(const std::vector<std::vector<SampleGenerateInfo_1d>>& sampleFunctions, const char* testName, const char* fileNamePrefix)
{
    DoIntegrationTest(sampleFunctions, testName, fileNamePrefix, ::Exp, e - 1.0f);
}

void _1d::Tests::Integration::Quadratic(const std::vector<std::vector<SampleGenerateInfo_1d>>& sampleFunctions, const char* testName, const char* fileNamePrefix)
{
    DoIntegrationTest(sampleFunctions, testName, fileNamePrefix, ::Quadratic, 3.0f);
}