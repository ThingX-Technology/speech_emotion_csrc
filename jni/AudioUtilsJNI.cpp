#include <iostream>
#include <vector>
#include <complex>
#include <string>
#include "librosa.h" // 确保 librosa.h 位于包含路径中

int main() {
    // 模拟输入信号 x（例如 1 秒长度的纯音频信号）
    int sr = 16000; // 采样率
    std::vector<float> x(sr, 0.0f); // 模拟长度为1秒的音频数据（全0）
    for (size_t i = 0; i < x.size(); ++i) {
        x[i] = 0.5f * std::sin(2 * M_PI * 440 * i / sr); // 440Hz 的正弦波
    }

    // 参数设置
    int n_fft = 400;
    int n_hop = 160;
    std::string window = "hann";
    bool center = false;
    std::string pad_mode = "reflect";
    float power = 2.f;
    int n_mel = 40;
    int fmin = 80;
    int fmax = 7600;
    int n_mfcc = 20;
    bool norm = true;
    int type = 2;

    // 计算短时傅里叶变换系数 (STFT)
    std::vector<std::vector<std::complex<float>>> X = librosa::Feature::stft(
        x, n_fft, n_hop, window, center, pad_mode
    );
    std::cout << "STFT computed, size: " << X.size() << " x " << X[0].size() << std::endl;

    // 计算梅尔频谱图 (Mel Spectrogram)
    std::vector<std::vector<float>> mels = librosa::Feature::melspectrogram(
        x, sr, n_fft, n_hop, window, center, pad_mode, power, n_mel, fmin, fmax
    );
    std::cout << "Mel Spectrogram computed, size: " << mels.size() << " x " << mels[0].size() << std::endl;

    // 计算梅尔频率倒谱系数 (MFCC)
    std::vector<std::vector<float>> mfcc = librosa::Feature::mfcc(
        x, sr, n_fft, n_hop, window, center, pad_mode, power, n_mel, fmin, fmax, n_mfcc, norm, type
    );
    std::cout << "MFCC computed, size: " << mfcc.size() << " x " << mfcc[0].size() << std::endl;

    return 0;
}
