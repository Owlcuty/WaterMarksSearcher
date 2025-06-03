import cv2
import os
import numpy as np
import random
from glob import glob

# Пути
watermark_path = "./watermark_template.png"
negative_dir = "./dataset/train/negative"
output_dir = "./dataset/train/positive"

# Загрузка watermark
watermark = cv2.imread(watermark_path, cv2.IMREAD_UNCHANGED)
if watermark is None:
    raise FileNotFoundError("Watermark not found")

# Добавим альфа-канал, если его нет
if watermark.shape[2] == 3:
    watermark = cv2.cvtColor(watermark, cv2.COLOR_BGR2BGRA)

# Загрузка негативных фонов
backgrounds = glob(os.path.join(negative_dir, "*.png"))
random.shuffle(backgrounds)

def overlay(img, wm, alpha, pos):
    h, w = img.shape[:2]
    wm = cv2.resize(wm, (int(w * 0.9), int(h * 0.1)))

    # Положение
    x, y = pos
    wm_h, wm_w = wm.shape[:2]
    if y + wm_h > h or x + wm_w > w:
        return img  # не помещается

    roi = img[y:y+wm_h, x:x+wm_w]
    wm_rgb = wm[:, :, :3]
    wm_alpha = (wm[:, :, 3] / 255.0 * alpha).reshape(wm_h, wm_w, 1)

    blended = roi * (1 - wm_alpha) + wm_rgb * wm_alpha
    img[y:y+wm_h, x:x+wm_w] = blended.astype(np.uint8)
    return img

def generate_variants(n=200):
    for i in range(n):
        bg_path = random.choice(backgrounds)
        bg = cv2.imread(bg_path)
        if bg is None:
            continue

        bg = cv2.resize(bg, (224, 224))  # под размер модели
        alpha = random.uniform(0.3, 0.7)
        x = random.randint(0, int(bg.shape[1] * 0.1))  # по X — сдвиг
        y = random.randint(int(bg.shape[0] * 0.85), int(bg.shape[0] * 0.9))  # снизу

        out = overlay(bg, watermark, alpha, (x, y))

        out_path = os.path.join(output_dir, f"synthetic_{i:04}.png")
        cv2.imwrite(out_path, out)

        if i % 25 == 0:
            print(f"Generated {i} images")

generate_variants(300)
