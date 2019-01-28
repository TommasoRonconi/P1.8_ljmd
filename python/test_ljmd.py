import unittest
from ljmd import *


class Test(unittest.TestCase):
    """
     Class used to test functionality of the class 
    """

    def test_check_read_data_from_file(self):
        """

        """
        list = read_inp("data/argon_108.inp")
        string_list = list[6:9]
        del list[6:9]
        self.assertListEqual(
            sorted(string_list), sorted(['argon_108.rest', 'argon_108.xyz', 'argon_108.dat']))
        self.assertListEqual(sorted(list), sorted([108, 39.948, 0.2379, 3.405, 8.5,
                                                   17.158, 10000.0, 5.0, 100.0]))





if __name__ == '__main__':
    
    unittest.main(verbosity=2)
