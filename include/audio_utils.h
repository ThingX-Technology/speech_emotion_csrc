#ifndef AUDIO_UTILS_H
#define AUDIO_UTILS_H

#include <vector>
#include <string>

// 提取MFCC特征函数声明
std::vector<float> extractMFCC(const std::string& audioFilePath, int sampleRate = 44100, int n_mfcc = 40);

#endif // AUDIO_UTILS_H
