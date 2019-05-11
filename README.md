Changelog:

03/05 (Friday):
- Thêm mảng hai chiều Pixels2D và Pixels2D_HSV cho struct Bitmap.
- Viết hàm chuyển dữ liệu từ pixels sang Pixels2D và ngược lại.
- Viết hàm chuyển không gian màu RGB sang HSV và ngược lại.

04/05 (Saturday):
- Đổi tên file Bitmap1.cpp -> Bitmap.cpp
- Đổi tên file Bitmap2.cpp -> Effect.cpp
- Đem hai hàm GetPixel và SetPixel từ Effect.cpp sang Bitmap.cpp
- Thêm hai hàm BGR2Gray và BGR2Binary của Nhi.
- Chỉnh sửa file header.

11/05 (Saturday):
- Đổi kiểu dữ liệu 
    unsigned char *pixels
->  vector<unsigned char> pixels;

- Sửa lại hàm 
    int LoadBitmap(const char *fname, Bitmap &bmp);
->  Bitmap LoadBitmap(string fname);
    Bitmap trả về đã có sẵn các mảng Pixels2D và Pixels2D_HSV

- Thêm 2 hàm
    void copyPixels2D(Bitmap &bmp, Bitmap &new_bmp);
    void copyPixels2D_HSV(Bitmap &bmp, Bitmap &new_bmp);

- Xóa hàm (vì ko cần nữa)
    void DisposeBitmap(Bitmap &bmp);

- Các hàm còn lại sửa lại cho phù hợp.
- Trong các hàm convert/ copy mảng đã kiểm tra điều kiện tồn tại mảng nguồn, nếu ko tồn tại thì sẽ gọi hàm phù hợp để tạo ra mảng nguồn.

- Các hàm trong Effect.cpp cần được viết theo khuôn mẫu sau:
    Bitmap Name_of_function(Bitmap &bmp, args...)
    {
        Bitmap new_bmp;
        // Nếu chỉ cần dùng mảng Pixels2D thôi thì:
        copyPixels2D(bmp, new_bmp);
        // Nếu chỉ cần dùng mảng Pixels2D_HSV thôi thì:
        copyPixels2D_HSV(bmp, new_bmp);
        //---------------------------------//
        //-------Chỉnh sửa ở đây-----------//
        //---------------------------------//
        Pixels2D_to_pixels(new_bmp); // trong này đã có bước HSV2BGR rồi
        // tính lại height, width, rowSize, nếu ko đổi thì vẫn gán giá trị vào
        new_bmp.height = bmp.height;
        new_bmp.width = bmp.width;
        new_bmp.rowSize = bmp.rowSize;
        return new_bmp;
    }
