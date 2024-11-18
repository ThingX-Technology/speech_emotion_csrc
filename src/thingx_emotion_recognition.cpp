//#include <onnxruntime_cxx_api.h>
//#include <iostream>
//#include <string>
//#include <vector>
//#include <fstream>
//#include <algorithm>
//#include <json.hpp>
//
//using json = nlohmann::json;
//
//// 加载 scaler 参数
//void load_scaler_params(const std::string& file_path, std::vector<float>& mean, std::vector<float>& scale) {
//    std::ifstream file(file_path);
//    if (!file.is_open()) {
//        throw std::runtime_error("无法打开文件: " + file_path);
//    }
//
//    try {
//        json scaler_json;
//        file >> scaler_json;
//
//        if (scaler_json.contains("mean") && scaler_json.contains("scale")) {
//            mean = scaler_json["mean"].get<std::vector<float>>();
//            scale = scaler_json["scale"].get<std::vector<float>>();
//        }
//        else {
//            throw std::runtime_error("文件内容缺少 'mean' 或 'scale' 键！");
//        }
//    }
//    catch (const std::exception& e) {
//        throw std::runtime_error("加载 scaler 参数时出错: " + std::string(e.what()));
//    }
//}
//
//std::string predict_emotion(const std::vector<float>& mfcc_features, const std::vector<float>& mean, const std::vector<float>& scale) {
//    // 创建 ONNX Runtime 环境
//    Ort::Env env(ORT_LOGGING_LEVEL_WARNING, "EmotionRecognition");
//    Ort::SessionOptions session_options;
//    session_options.SetIntraOpNumThreads(1);
//    session_options.SetGraphOptimizationLevel(GraphOptimizationLevel::ORT_ENABLE_ALL);
//
//    // 模型路径
//    const std::wstring model_path = L"C:/Users/edith/dl_workplace/thingx_emotion_recognition/models/thingx_emotion_model.onnx";
//    Ort::Session session(env, model_path.c_str(), session_options);
//    std::cout << "模型加载成功！" << std::endl;
//
//    // 获取输入和输出节点名称
//    Ort::AllocatorWithDefaultOptions allocator;
//    std::vector<const char*> input_names;
//    std::vector<const char*> output_names;
//
//    std::cout << "模型输入名称：" << std::endl;
//    for (size_t i = 0; i < session.GetInputCount(); i++) {
//        Ort::AllocatedStringPtr input_name = session.GetInputNameAllocated(i, allocator);
//        std::cout << "  - " << input_name.get() << std::endl;
//        input_names.push_back(input_name.get());
//    }
//
//    std::cout << "模型输出名称：" << std::endl;
//    for (size_t i = 0; i < session.GetOutputCount(); i++) {
//        Ort::AllocatedStringPtr output_name = session.GetOutputNameAllocated(i, allocator);
//        std::cout << "  - " << output_name.get() << std::endl;
//        output_names.push_back(output_name.get());
//    }
//
//    // 应用标准化
//    std::vector<float> features = mfcc_features;
//    for (size_t i = 0; i < features.size(); i++) {
//        features[i] = (features[i] - mean[i]) / scale[i];
//    }
//
//    // 定义输入张量的形状
//    std::vector<int64_t> input_shape = { 1, 1, static_cast<int64_t>(features.size()) };
//
//    Ort::MemoryInfo memory_info = Ort::MemoryInfo::CreateCpu(OrtArenaAllocator, OrtMemTypeDefault);
//    Ort::Value input_tensor = Ort::Value::CreateTensor<float>(
//        memory_info, features.data(), features.size(), input_shape.data(), input_shape.size()
//    );
//
//    // 运行推理
//    auto output_tensors = session.Run(Ort::RunOptions{ nullptr }, input_names.data(), &input_tensor, 1, output_names.data(), 1);
//
//    // 获取输出并找到最大值的索引
//    float* output_array = output_tensors[0].GetTensorMutableData<float>();
//    int max_index = std::max_element(output_array, output_array + 8) - output_array;
//
//    // 假设类别标签
//    std::vector<std::string> label_classes = {
//        "happy", "sad", "angry", "fearful", "disgust", "surprised", "neutral", "boredom"
//    };
//
//    return label_classes[max_index];
//}
//
//int main() {
//    try {
//        // 加载标准化参数
//        std::vector<float> mean, scale;
//        load_scaler_params("C:\\Users\\edith\\dl_workplace\\thingx_emotion_recognition\\models\\scaler_params.json", mean, scale);
//
//
//        std::vector<float> mfcc_features(40, 0.5f);  
//
//        // 调用推理函数
//        std::string emotion = predict_emotion(mfcc_features, mean, scale);
//        std::cout << "预测情感: " << emotion << std::endl;
//
//    }
//    catch (const Ort::Exception& e) {
//        std::cerr << "ONNX Runtime 异常: " << e.what() << std::endl;
//        return -1;
//    }
//    catch (const std::exception& e) {
//        std::cerr << "通用异常: " << e.what() << std::endl;
//        return -1;
//    }
//
//    return 0;
//}
