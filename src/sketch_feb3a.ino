#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP3XX.h>

#define BMP_CS 5    // BMP388'in Chip Select (CS) pini
#define BMP_SCK 18  // SPI Saat (SCK)
#define BMP_MISO 19 // SPI Veri Çıkışı (MISO)
#define BMP_MOSI 23 // SPI Veri Girişi (MOSI)

#define SEALEVELPRESSURE_HPA (1013.25) // Deniz seviyesi basıncı

Adafruit_BMP3XX bmp;

void setup() {
    Serial.begin(115200);

    if (!bmp.begin_SPI(BMP_CS, BMP_SCK, BMP_MISO, BMP_MOSI)) {
        Serial.println("BMP388 sensörü bulunamadı! Lütfen bağlantıları kontrol edin.");
        while (1);
    }

    // Sensör ayarları
    bmp.setTemperatureOversampling(BMP3_OVERSAMPLING_8X);
    bmp.setPressureOversampling(BMP3_OVERSAMPLING_4X);
    bmp.setIIRFilterCoeff(BMP3_IIR_FILTER_COEFF_3);
}

void loop() {
    if (!bmp.performReading()) {
        Serial.println("Ölçüm başarısız!");
        return;
    }

    // Basınç, Sıcaklık ve İrtifa hesaplama
    float pressure = bmp.pressure / 100.0; // hPa cinsine çevirmek için
    float temperature = bmp.temperature; // °C
    float altitude = bmp.readAltitude(SEALEVELPRESSURE_HPA); // Metre cinsinden

    // Seri monitöre yazdır
    Serial.print("Basınç: "); Serial.print(pressure); Serial.println(" hPa");
    Serial.print("Sıcaklık: "); Serial.print(temperature); Serial.println(" °C");
    Serial.print("İrtifa: "); Serial.print(altitude); Serial.println(" m");
    Serial.println("-----------------------------------");

    delay(1000); // 1 saniye bekleyerek sürekli okuma yap
}
