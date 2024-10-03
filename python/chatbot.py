# pip install nltk scikit-learn
import nltk
from nltk.chat.util import Chat, reflections

nltk.download('punkt')

# Definir pares de padrões e respostas
pairs = [
    [
        r"meu nome é (.*)",
        ["Olá %1, como posso ajudar você?",]
    ],
    [
        r"oi|olá|e aí",
        ["Oi!", "Olá!", "E aí?",]
    ],
    [
        r"qual é a sua função?|qual e a sua funcao?",
        ["Eu estou aqui para ajudar você com perguntas simples.",]
    ],
    [
        r"me fale uma praia em floripa|uma praia em floripa",
        ["Praia da Joaquina: Famosa por suas dunas e ondas, é um destino popular entre surfistas e praticantes de sandboard.",
         "Ilha do Campeche: Uma pequena ilha localizada em frente à Praia do Campeche, famosa por suas águas cristalinas e trilhas arqueológicas.",
         "Praia dos Ingleses: Uma das mais movimentadas do norte da ilha, conhecida por suas águas calmas e infraestrutura turística completa.",
         "Praia de Canasvieiras: Muito popular entre turistas, especialmente argentinos, tem águas calmas e é ideal para famílias e atividades náuticas.",]
    ],
]

#Chat do NLTK
chatbot = Chat(pairs, reflections)

# Função principal
def iniciar_chat():
    print("Olá! Eu sou um chatbot. Digite 'adeus' para sair.")
    while True:
        entrada = input("Você: ")
        if entrada.lower() == "adeus":
            print("Jarvis_shoppe: Tchau! Tenha um ótimo dia!")
            break
        resposta = chatbot.respond(entrada)
        print(f"Jarvis_shoppe: {resposta}")

# Iniciar o chatbot
iniciar_chat()
