from linkedlist import LinkedListBasic

class CacheSimulator:
    def __init__(self, cache_size):
        self.cache_size = cache_size
        self.cache = LinkedListBasic()
        self.cache_dict = {} #LinkedList내에서 찾는것이 너무 느려 딕셔너리 속성을 추가했습니다.
        self.cache_hit = 0
        self.tot_cnt = 0
    
    def do_sim(self, page):
        if page in self.cache_dict: #page가 있는지 확인
            self.cache_hit += 1 # 캐쉬 적중시
            self.cache.remove(page) #해당 page가 있는 노드를 제거한다
            self.cache.insert(0, page) # head를 MRU로 하여 page를 추가한다. 
        else: # 캐쉬 적중 실패
            if self.cache.size() >= self.cache_size: #캐쉬 사이즈를 넘는 지 확인
                self.cache_dict.pop(self.cache.get(self.cache.size() - 1)) 
                self.cache.pop(self.cache.size() - 1) #맨끝 LRU의 위치에 있는 노드 제거

            self.cache.insert(0, page) #새로운 데이터를 MRU에 저장한다.
            self.cache_dict[page] = True
        self.tot_cnt += 1
    
    def print_stats(self):
        print("Cache size =", self.cache_size, "Cache hit =", self.cache_hit, "Hit ratio =", self.cache_hit / self.tot_cnt)


if __name__ == "__main__":
    
    data_file = open("C:/Users/jipo0/OneDrive/바탕 화면/숭실숭실/2024-1/자료구조/ds_2024/ds_2024/lru_sim/linkbench.trc")
    lines = data_file.readlines()
    for cache_size in range(100, 1001, 100):
        cache_sim = CacheSimulator(cache_size)
        for line in lines:
            page = line.split()[0]
            cache_sim.do_sim(page)
        
        cache_sim.print_stats()
