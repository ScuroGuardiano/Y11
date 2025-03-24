# C++ jest dosłownie najgorszym językiem OOP jaki istnieje, a oto argumenty:

- Metody generyczne nie mogą być wirtualne.
- Aby korzystać z dobrodziejstw OOP trzeba się pierdzielić ze wskaźnikami w wielu przypadkach.
- Metody generyczne nie mogą być zdefiniowane w pliku `.cpp`
- Metody constexpr nie mogą być zdefiniowane w pliku `.cpp`
- Dwa powyższe powodują totalny rozpierdol w kodzie, część metod ma implementację w pliku `.cpp`, część w `.hpp`, burdel.
- Implicit copy - chyba żaden język OOP nie pozwala na niejawne kopiowanie obiektów, szczególnie w przypadku manualnego zarządzania pamięcią implicit copy może być skrajnie unsafe i prowadzić do powalonych błędów. Języki wspierające copy, jak np. Rust mają to zaimplementowanie jawnie, trzeba wywować `.clone` na obiekcie. Inne nie mają tego wcale i trzeba ręcznie oraz świadomie napisać metodę kopiującą.
- Sprawdzanie typu  

    ```cpp
    if (Composite* composite = dynamic_cast<Composite*>((*it).get()))
    ```

    To jest jakieś, k###a nieporozumienie, meanwhile w C#:  

    ```cs
    if (el is Composite composite)
    ```
