import os
import cv2
import shutil

def is_truncated_image(img_path):
    """Проверяет, является ли изображение битым/усечённым"""
    try:
        img = cv2.imread(img_path)
        if img is None:
            return True
        
        # Дополнительная проверка через попытку декодирования
        with open(img_path, 'rb') as f:
            f.seek(-24, os.SEEK_END)
            if not f.read().endswith(b'IEND\xaeB`\x82'):
                return True
                
        return False
    except Exception as e:
        print(f"Ошибка при проверке {img_path}: {str(e)}")
        return True

def find_and_move_truncated_images(source_dir, dest_dir):
    """Находит и перемещает битые изображения"""
    if not os.path.exists(source_dir):
        print(f"Папка {source_dir} не существует!")
        return

    os.makedirs(dest_dir, exist_ok=True)
    truncated_count = 0

    for filename in os.listdir(source_dir):
        if filename.lower().endswith(('.png', '.jpg', '.jpeg')):
            filepath = os.path.join(source_dir, filename)
            if is_truncated_image(filepath):
                dest_path = os.path.join(dest_dir, filename)
                os.remove(filepath)
                print(f"Перемещено битое изображение: {filename}")
                truncated_count += 1

    print(f"\nГотово! Найдено и перемещено {truncated_count} битых изображений.")

if __name__ == "__main__":
    source_directory = "dataset/train/positive"
    dest_directory = "dataset/train/negative_truncated"
    
    find_and_move_truncated_images(source_directory, dest_directory)