from llama_cpp import Llama
from nltk.translate.bleu_score import corpus_bleu, SmoothingFunction

llm = Llama(model_path=".\qwen2.5-3b-instruct-abliterated-q4_k_m.gguf", verbose=False,)


prompt = "Where is Southeast University located?"
output = llm.create_chat_completion(
    messages=[{
        "role": "user",
        "content": prompt
    }],
    max_tokens=200,
    stream=False,
)
answer = output["choices"][0]["message"]["content"]
print(answer)