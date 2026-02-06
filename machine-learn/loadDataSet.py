#Carregar os dados extraídos do LtSpice em dataset.txt
import numpy as np


def load_ltspice_txt(filename):

    vg_list = []
    vout_list = []
    vk_list = [] 

    with open(filename, "r") as f:
        for line in f:
            line = line.strip()

            if not line: continue
            if line.lower().startswith("step"): continue
            if line.lower().startswith("vg"): continue

            parts = line.split()
            if len(parts) < 2:continue

            try:
                vg = float(parts[0])
                vout = float(parts[1])
                vk = float(parts[3])
            except ValueError:
                continue

            vg_list.append(vg)
            vout_list.append(vout)
            vk_list.append(vk)

    if len(vg_list) == 0:
        raise RuntimeError("Nenhum dado válido foi lido!")

    vg = np.array(vg_list, dtype=np.float32)
    vout = np.array(vout_list, dtype=np.float32)
    vk = np.array(vk_list, dtype=np.float32)

    return vg, vk, vout


def build(txt_file):
    vg, vk, vout = load_ltspice_txt(txt_file)

    vgk = vg - vk

    X = (vgk / 5.0).reshape(-1, 1)

    vout_min = vout.min()
    vout_max = vout.max()

    Y = 2.0 * (vout - vout_min) / (vout_max - vout_min) - 1.0


    return X, Y
