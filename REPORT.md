# Report on the result of the objective

# objective 1
Setelah saya melakukan analisis dan experiment pada beberapa ukuran window, saya menemukan bahwa ukuran window yang bisa di bilang ideal untuk proses segment detection terhadap resolusi window canvas ini adalah 3×3, 5×5, dan 7×7.
ketiga ukuran ini saya pilih agar proses scanning tidak melakukan scanning full pada area canvas tanpa melewati boundary dari canvas yang dapat menyebabkan crash.

# objective 2
lalu di obejctive 2 saya melakukan analisis terhadap semua window yang diambil untuk mencari pola window yang sesuai dengan karakteristik segment. Program mendeteksi kesesuaian pola pixel density dari window hasil scan itu, jika sebuah window minimal 60% dari pixel dalam satu baris, kolom, atau diagonal, maka window tersebut akan dikategorikan sebagai segment-like pattern.

Dari testing, dapat dilihat bahwa beberapa window berhasil dikenali sebagai pola horizontal, vertikal, dan diagonal.
metode ini lebih baik dan flexibel dari cara pengecekan berdasarkan invidiual pixel yang membuat segment line tidak terdeteksi, karena cara ini dapat mengenali garis yang tebal, tidak rata and bahkan yang kurang lengkap tapi merupakan bagian dari garis

Program lalu membuat file report.md setelah melakukan analisa untuk memberikan data hasil scan, bersama dengan hasil dump window non-kosong untuk di analisa lebih lanjut jika perlu.

# objective 3