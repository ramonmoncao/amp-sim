import onnxruntime as ort
import numpy as np


def test_triode_model(model_path):
    try:
        session = ort.InferenceSession(model_path)
    except Exception as e:
        print(f"Erro ao carregar o modelo: {e}")
        return

    input_name = session.get_inputs()[0].name
    output_name = session.get_outputs()[0].name

    vgk_real = np.linspace(-5.0, 5.0, 101).astype(np.float32)
    vgk_norm = vgk_real / 5.0

    print(f"{'Vgk (Entrada)':<15} | {'Vout (Saída prevista)':<20}")
    print("-" * 40)

    for v_norm, v_real in zip(vgk_norm, vgk_real):
        input_data = np.array([[v_norm]], dtype=np.float32)

        prediction = session.run(
            [output_name],
            {input_name: input_data}
        )

        vout = float(prediction[0][0][0])

        print(f"{v_real:6.2f} V        | {vout:.6f}")


if __name__ == "__main__":
    test_triode_model("triode_model.onnx")
