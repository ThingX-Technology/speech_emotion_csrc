#include <iostream>
#include <vector>
#include <complex>
#include <string>
#include "librosa.h" // ȷ�� librosa.h λ�ڰ���·����

int main() {
    // ģ�������ź� x������ 1 �볤�ȵĴ���Ƶ�źţ�
    int sr = 16000; // ������
    std::vector<float> x(sr, 0.0f); // ģ�ⳤ��Ϊ1�����Ƶ���ݣ�ȫ0��
    for (size_t i = 0; i < x.size(); ++i) {
        x[i] = 0.5f * std::sin(2 * M_PI * 440 * i / sr); // 440Hz �����Ҳ�
    }

    // ��������
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

    // �����ʱ����Ҷ�任ϵ�� (STFT)
    std::vector<std::vector<std::complex<float>>> X = librosa::Feature::stft(
        x, n_fft, n_hop, window, center, pad_mode
    );
    std::cout << "STFT computed, size: " << X.size() << " x " << X[0].size() << std::endl;

    // ����÷��Ƶ��ͼ (Mel Spectrogram)
    std::vector<std::vector<float>> mels = librosa::Feature::melspectrogram(
        x, sr, n_fft, n_hop, window, center, pad_mode, power, n_mel, fmin, fmax
    );
    std::cout << "Mel Spectrogram computed, size: " << mels.size() << " x " << mels[0].size() << std::endl;

    // ����÷��Ƶ�ʵ���ϵ�� (MFCC)
    std::vector<std::vector<float>> mfcc = librosa::Feature::mfcc(
        x, sr, n_fft, n_hop, window, center, pad_mode, power, n_mel, fmin, fmax, n_mfcc, norm, type
    );
    std::cout << "MFCC computed, size: " << mfcc.size() << " x " << mfcc[0].size() << std::endl;

    return 0;
}
