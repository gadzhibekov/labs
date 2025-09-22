import random
import tkinter as tk
from tkinter import ttk, messagebox, simpledialog
import threading

class GeneticProductOptimizer:
    def __init__(self, root):
        self.root = root
        self.root.title("Генетический оптимизатор закупок")
        self.root.geometry("900x700")
        self.products = []
        self.generate_products()
        self.best_solution = None
        self.population_size = 50
        self.generations = 30
        self.mutation_rate = 0.1
        self.create_widgets()

    def generate_products(self):
        categories = ["Картофель", "Морковь", "Лук", "Капуста", "Яблоки", 
                      "Говядина", "Курица", "Свинина", "Молоко", "Сыр",
                      "Рис", "Гречка", "Макароны", "Масло", "Сахар"]

        for i in range(1, 51):
            self.products.append({
                "id": i,
                "name": f"{random.choice(categories)} {i}",
                "min": random.randint(1, 5),
                "max": random.randint(10, 50),
                "price": round(random.uniform(10, 200), 2)
            })

    def create_widgets(self):
        control_frame = ttk.Frame(self.root, padding=10)
        control_frame.pack(fill=tk.X)

        ttk.Label(control_frame, text="Бюджет:").pack(side=tk.LEFT)
        self.budget_entry = ttk.Entry(control_frame, width=15)
        self.budget_entry.pack(side=tk.LEFT, padx=5)
        self.budget_entry.insert(0, "10000")
        self.run_button = ttk.Button(control_frame, text="Запустить оптимизацию", command=self.run_genetic_algorithm)
        self.run_button.pack(side=tk.LEFT, padx=5)
        ttk.Button(control_frame, text="Редактировать продукты", command=self.edit_products).pack(side=tk.LEFT)

        self.result_frame = ttk.LabelFrame(self.root, text="Результаты", padding=10)
        self.result_frame.pack(fill=tk.BOTH, expand=True, padx=10, pady=10)
        self.result_text = tk.Text(self.result_frame, height=20, wrap=tk.WORD)
        self.result_text.pack(fill=tk.BOTH, expand=True)

        self.status = ttk.Label(self.root, text="Готов к работе", relief=tk.SUNKEN)
        self.status.pack(fill=tk.X, padx=10, pady=5)

    def edit_products(self):
        edit_win = tk.Toplevel(self.root)
        edit_win.title("Редактирование продуктов")
        edit_win.geometry("800x500")

        tree = ttk.Treeview(edit_win, columns=("name", "min", "max", "price", "min_cost", "max_cost"), show="headings", height=20)
        tree.heading("#0", text="ID")
        tree.heading("name", text="Наименование")
        tree.heading("min", text="Мин")
        tree.heading("max", text="Макс")
        tree.heading("price", text="Цена")
        tree.heading("min_cost", text="Мин. стоимость")
        tree.heading("max_cost", text="Макс. стоимость")

        vsb = ttk.Scrollbar(edit_win, orient="vertical", command=tree.yview)
        hsb = ttk.Scrollbar(edit_win, orient="horizontal", command=tree.xview)
        tree.configure(yscrollcommand=vsb.set, xscrollcommand=hsb.set)
        tree.grid(row=0, column=0, sticky="nsew")
        vsb.grid(row=0, column=1, sticky="ns")
        hsb.grid(row=1, column=0, sticky="ew")

        btn_frame = ttk.Frame(edit_win)
        btn_frame.grid(row=2, column=0, columnspan=2, pady=5)
        ttk.Button(btn_frame, text="Изменить", command=lambda: self.edit_product(tree)).pack(side=tk.LEFT, padx=5)

        for p in self.products:
            min_cost = p['min'] * p['price']
            max_cost = p['max'] * p['price']
            tree.insert("", tk.END, text=p['id'], values=(p['name'], p['min'], p['max'], p['price'], round(min_cost, 2), round(max_cost, 2)))

        edit_win.grid_rowconfigure(0, weight=1)
        edit_win.grid_columnconfigure(0, weight=1)

    def edit_product(self, tree):
        selected = tree.selection()

        if not selected:
            messagebox.showwarning("Предупреждение", "Выберите продукт для редактирования")
            return

        item = selected[0]
        item_id = int(tree.item(item, "text"))
        product = next((p for p in self.products if p['id'] == item_id), None)

        if product is None:
            messagebox.showerror("Ошибка", "Продукт не найден")
            return

        new_name = simpledialog.askstring("Редактировать наименование", "Введите наименование:", initialvalue=product['name'])
        if new_name is None:
            return
        new_min = simpledialog.askinteger("Редактировать мин", "Введите минимальное количество:", initialvalue=product['min'], minvalue=0)
        if new_min is None:
            return
        new_max = simpledialog.askinteger("Редактировать макс", "Введите максимальное количество:", initialvalue=product['max'], minvalue=new_min)
        if new_max is None:
            return
        new_price = simpledialog.askfloat("Редактировать цену", "Введите цену:", initialvalue=product['price'], minvalue=0)
        if new_price is None:
            return

        product['name'] = new_name
        product['min'] = new_min
        product['max'] = new_max
        product['price'] = round(new_price, 2)

        min_cost = product['min'] * product['price']
        max_cost = product['max'] * product['price']
        tree.item(item, values=(product['name'], product['min'], product['max'], product['price'], round(min_cost, 2), round(max_cost, 2)))

    def run_genetic_algorithm(self):
        try:
            budget = float(self.budget_entry.get())
            if budget <= 0:
                raise ValueError
        except ValueError:
            messagebox.showerror("Ошибка", "Введите корректный бюджет")
            return

        self.run_button.config(state=tk.DISABLED)
        self.status.config(text="Запуск оптимизации...")
        self.result_text.delete(1.0, tk.END)

        thread = threading.Thread(target=self.genetic_algorithm, args=(budget,))
        thread.start()

    def genetic_algorithm(self, budget):
        def fitness(solution):
            total_cost = 0
            total_quantity = 0
            for i, qty in enumerate(solution):
                p = self.products[i]
                if qty < p['min'] or qty > p['max']:
                    return -1
                total_cost += qty * p['price']
                total_quantity += qty
            if total_cost > budget:
                return -1
            return total_quantity

        def create_individual():
            individual = []
            for p in self.products:
                individual.append(random.randint(p['min'], p['max']))
            return individual

        def mutate(individual):
            for i in range(len(individual)):
                if random.random() < self.mutation_rate:
                    p = self.products[i]
                    individual[i] = random.randint(p['min'], p['max'])

        def crossover(parent1, parent2):
            point = random.randint(1, len(parent1) - 2)
            child1 = parent1[:point] + parent2[point:]
            child2 = parent2[:point] + parent1[point:]
            return child1, child2

        population = [create_individual() for _ in range(self.population_size)]
        best_solution = None
        best_fitness = -1

        for gen in range(self.generations):
            scored = [(ind, fitness(ind)) for ind in population]
            scored = [x for x in scored if x[1] >= 0]
            scored.sort(key=lambda x: x[1], reverse=True)

            if not scored:
                population = [create_individual() for _ in range(self.population_size)]
                continue

            if scored[0][1] > best_fitness:
                best_fitness = scored[0][1]
                best_solution = scored[0][0]

            self.root.after(0, self.update_status, f"Поколение {gen+1}/{self.generations}, лучший результат: {best_fitness}")

            selected = []
            while len(selected) < self.population_size:
                a, b = random.sample(scored, 2)
                selected.append(a[0] if a[1] > b[1] else b[0])

            next_population = []
            for i in range(0, self.population_size, 2):
                parent1 = selected[i]
                parent2 = selected[min(i+1, self.population_size-1)]
                child1, child2 = crossover(parent1, parent2)
                next_population.extend([child1, child2])

            for ind in next_population:
                mutate(ind)

            population = next_population[:self.population_size]

        self.best_solution = best_solution
        self.root.after(0, self.show_result, best_solution, best_fitness, budget)
        self.root.after(0, lambda: self.run_button.config(state=tk.NORMAL))
        self.root.after(0, lambda: self.status.config(text="Оптимизация завершена"))

    def update_status(self, text):
        self.status.config(text=text)

    def show_result(self, solution, fitness_value, budget):
        if solution is None:
            self.result_text.insert(tk.END, "Не удалось найти допустимое решение.\n")
            return

        total_cost = 0
        self.result_text.insert(tk.END, f"Лучшее решение (суммарное количество: {fitness_value}):\n\n")
        self.result_text.insert(tk.END, f"{'Продукт':<30}{'Количество':>10}{'Цена за ед.':>15}{'Стоимость':>15}\n")
        self.result_text.insert(tk.END, "-"*70 + "\n")

        for i, qty in enumerate(solution):
            p = self.products[i]
            cost = qty * p['price']
            total_cost += cost
            self.result_text.insert(tk.END, f"{p['name']:<30}{qty:>10}{p['price']:>15.2f}{cost:>15.2f}\n")

        self.result_text.insert(tk.END, "-"*70 + "\n")
        self.result_text.insert(tk.END, f"Общий бюджет: {budget:.2f}\n")
        self.result_text.insert(tk.END, f"Общая стоимость: {total_cost:.2f}\n")


if __name__ == "__main__":
    root = tk.Tk()
    app = GeneticProductOptimizer(root)
    root.mainloop()