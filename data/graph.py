import matplotlib.pyplot as plt
# Dados atualizados
langs = ['C', 'Node.js', 'Python']
rps = [10384.67, 6572.11, 9940.31]
mean_time = [9.630, 15.216, 10.060]
max_time = [11, 37, 12]
transfer = [1298.08, 821.51, 1242.54]
falhas = [0, 0, 0]

# Estilo geral
plt.style.use('seaborn-v0_8-dark-palette')
plt.rcParams['font.family'] = 'DejaVu Sans'
plt.figure(figsize=(14, 8))

# Paleta personalizada
colors = ['#4CAF50', '#2196F3', '#FF9800']

def plot_metric(position, data, title, ylabel):
    plt.subplot(2, 3, position)
    bars = plt.bar(langs, data, color=colors)
    plt.title(title, fontsize=14, fontweight='bold')
    plt.ylabel(ylabel, fontsize=12)
    plt.grid(axis='y', linestyle='--', alpha=0.6)
    for bar in bars:
        yval = bar.get_height()
        plt.text(bar.get_x() + bar.get_width() / 2, yval, f'{yval:.1f}',
                 ha='center', va='bottom', fontsize=10)

plot_metric(1, rps, 'RPS', 'Req/seg')
plot_metric(2, mean_time, 'Time Per req (ms) [mean]', 'ms')
plot_metric(3, max_time, 'Max Time Per Req (ms)', 'ms')
plot_metric(4, transfer, 'Transfer Rate', 'KB/s')
plot_metric(5, falhas, 'Fails', 'Qt')

# plt.tight_layout()
# plt.subplots_adjust(top=0.88)
plt.show()
