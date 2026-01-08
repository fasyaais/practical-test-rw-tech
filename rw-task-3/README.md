# **TASK 3** Multi Task
Pada tugas ini dibuat untuk menyelesaikan permasalahan dari multi task tanpa adanya blocking pada kode. Digunakannya RTOS dan mutex untuk mengantisipasi dari inconsistent data dan race condition.

> Task ini dibuat menggunakan PlatformIo.

## Requitments
Terdapat sebuah requirement

1. Buat sebuah program yang memungkinkan kedua task berjalan secara
bersamaan dan tetap dapat menggunakan sharedDataBuffer dengan aman.
2. Output boleh berupa simulasi ke console, misal :
`Sensor Task: Updating buffer...
Communication Task: Sending data...`

## Schematic 

![alt Schematic LED](./img/image.png)


## How to works

Pada tugas ini terdapat Task `Task Sensor` dan `Task Communication` yang berjalan bersamaan. Jika melakukan koding menggunakan cara seperti biasa kode akan bersifat bloking atau menungu proses sebelumnya selesai baru dia menjalankan tugas tersebut. 

Untuk mengatasi permasalahan tersebut digunakanlah RTOS dikarenakan bisa menjalankan secara bersamaan. Dikarenakan requitment meminta untuk kedua task tersebut bisa menggunakan data yang dibagikan maka diperlukan mutual exclusion (mutex) untuk  mengantisipasi inconsistent data karena task A yang sedang melakukan penambahan data yang belum lengkap sudah digunakan oleh TASK B untuk mengirim data tersebut. 


