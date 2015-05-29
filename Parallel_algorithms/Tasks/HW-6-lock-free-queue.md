## lock-free queue [lock-free-queue]

�������� ```lock-free queue``` + ��������� � ������� �������� (```quiescent points```) ��� ������� �������� ���������� ������ (```safe memory reclamation```)

������������ ������:  

Maged Michael, Michael Scott - Simple, Fast, and Practical Non-Blocking and Blocking Concurrent Queue Algorithms

---

����������, ��������� ������ ���� ���������.

---

�������� ����� - ���������� ����� ������������ ��������� ���������� ������:

A) ```node recycling: free-pool + tagged pointers```

����� ���������� ���� �� ���������� (������� ��� �����) �� ���������� � ����������� ��� ��������� ����� (```free-pool```). �����, ������� ��������� ������� � ���������, ������� �������� ����� ���� �� ����, � ������ � ������, ���� ��� �����������, ���������� ����� ����.

```free-pool``` ����� ������� ```lock-free``` ������ � ����� ������� ����� ��� ��, ��� � �������� ����/�������: ���� ����� ��������� � ����������� ������ � ������� ��� �� ����������. 

����������, ��� ������ ```lock-free-stack/queue``` ����� ������ ```lock-free stack``` � �������� ��������� ��������� ����� ������������ � ��� ������.


����� ���, ��� ���������� � ����������, ������� � ����� ������� ABA-�������� � ������ ```pop/dequeue```.

����� ���������� �� ABA-��������, ����������� ```tagged pointers``` - ���� �� ��������� � ������ ������ ����� ���������, ������� �� ��������� ```lock-free CAS```. ����� ������ ����� ����������� ��� ������ ����������, ��� ����� �������� (��� ����������� ������ �����������) ABA.

B) ```hazard pointers``` (��������� ���������)