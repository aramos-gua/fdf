from PIL import Image

def convert_image_to_fdf(image_path, output_path):
    img = Image.open(image_path).convert("L")  # Grayscale
    img = img.resize((100, 100))  # Resize to something manageable
    pixels = list(img.getdata())
    width, height = img.size

    with open(output_path, 'w') as f:
        for y in range(height):
            row = pixels[y*width:(y+1)*width]
            f.write(' '.join(str(p // 10) for p in row) + '\n')  # Scale z-values down

convert_image_to_fdf("/home/aramos/Pictures/bubbles.jpeg", "/home/aramos/fdf/test_maps/bubbles.fdf")
