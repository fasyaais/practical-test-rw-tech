# **TASK 2** Management Task
Pada tugas ini dibuat untuk menyelesaikan permasalahan dari permasalahan pembacaan sensor yang menunggu .Pada kasus ini menggunakan  protokol i2c sebagai contoh dari bus yang sama.

> Task ini dibuat menggunakan PlatformIo.

## Requitments
Terdapat sebuah spesifikasi & constaint dan requirement

Spesifikasi & constraint
---
1. Setiap sensor membutuhkan 40 ms untuk melakukan proses pembacaan data.
2. Kelima sensor menggunakan bus yang sama, sehingga pembacaan harus
dilakukan secara berurutan.
3. Setiap data sensor membutuhkan 40 ms untuk dikirim.
4. Setiap sensor harus mengirimkan data setiap 200 ms dengan toleransi maksimal
5ms.

Requirements
---
1. Buat sebuah program untuk menangani 5 sensor sehingga setiap sensor dapat:
   - Melakukan pembacaan data
   - Mengirimkan datanya dengan interval 200 ms dan tetap berada dalam
batas toleransi.
2. Proses pembacaan data dan pengiriman data tidak boleh menyebabkan sensor
lain melampaui batas toleransi waktu.
3. Program harus memastikan bahwa setiap sensor tetap mengirimkan data sesuai
jadwal meskipun terdapat keterlambatan pada proses baca/kirim.
4. Output boleh berupa simulasi ke console, misalnya log waktu pembacaan dan
pengiriman.

## Schematic 

![alt Schematic LED](./img/image.png)

|SENSOR| ADDRESS|
|-|-|
|MPU|0x69|
|RTC|0x68|

Secara default sensor MPU menggunakan alamat `0x68` sama seperti rtc, tetapi sensor MPU memiliki pin untuk merubah addr menjadi `0x69` ketika pin `AD0` diberikan tegangan.

## How to works

Pada task ini digunkan 2 sensor I2C MPU6050 & RTC, dikarenakna constraint harus memiliki 5 sensor maka dilakukan insiasi sebanyak 5 sensor. Tugas ini menggunakaa RTOS untuk melakukan managemen task.


