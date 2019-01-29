""""
    @authors: Herbert Nguruwe, 
    Thomas, Jesus 
"""
import unittest
from ljmd import *


class Test(unittest.TestCase):
    """
     Class used to test functionality of the class 
    """

    def test_check_read_data_from_file(self):
        """

        """
        list = read_inp("../examples/argon_108.inp")
        string_list = list[6:9]
        del list[6:9]
        self.assertListEqual(
            sorted(string_list), sorted(['argon_108.rest', 'argon_108.xyz', 'argon_108.dat']))
        self.assertListEqual(sorted(list), sorted([108, 39.948, 0.2379, 3.405, 8.5,
                                                   17.158, 10000.0, 5.0, 100.0]))

    def test_check_array_data(self):
        """
         We checked  for the data  for all x axis 
         send part end of 

        """
        #test starting values for r values
        self.assertListEqual(sorted(rx[:6]), sorted(
            [6.67103294321331, 1.06574058650169, -1.78412295775301, 9.81030288841332, 15.3247211142637, 2.11253838645732]))
        self.assertListEqual(sorted(ry[:6]), sorted(
            [-10.6146871435653, -3.33432278188177, -16.5259458407765, -5.82405963687712, -4.78053306974291, -4.72955953073222]))
        self.assertListEqual(sorted(rz[:6]), sorted(
            [12.6336939877734, -2.59038677851747, 4.61680014503288, 3.65645974729484, 8.26672732196501, 6.75738627120688]))

        #test starting values for v values
        self.assertListEqual(sorted(vx[:6]), sorted(
            [-0.0015643224621482283, 0.0004167671025765145, -0.0007561134956233392, -0.0010716463354369357, 0.0018845309488827741, 0.0006385093617706369]))
        self.assertListEqual(sorted(vy[:6]), sorted(
            [0.00048497508563925346, 2.2858522230176587e-05, 0.00040710138209103827, 0.0019399472344407333, -0.0009692965497960194, 0.002943996162594349]))
        self.assertListEqual(sorted(vz[:6]), sorted(
            [-0.00043352481732883966, -0.0006198504046274573, -0.00046520198934056357, 3.680520789201499e-05, -0.0005059063188932379, 0.00020290627741083355]))

        #test starting values for r values
        self.assertListEqual(sorted(rx[105:]), sorted(
            [13.713812197298, 18.2065606702052, -6.65121935702062]))
        self.assertListEqual(sorted(ry[105:]), sorted(
            [-0.358709470051391, -7.01462311401517, 1.49356278110318]))
        self.assertListEqual(sorted(rz[105:]), sorted(
            [8.46443111624972, 21.0114091185902, 20.6354475761263]))

        #test starting values for v values
        self.assertListEqual(sorted(vx[105:]), sorted(
            [0.0015850650475339276, -0.002020431342992367, -7.610709173848184e-05]))
        self.assertListEqual(sorted(vy[105:]), sorted(
            [-6.443414592180603e-06, 6.342828095437782e-05, 0.0006574268899540497]))
        self.assertListEqual(sorted(vz[105:]), sorted(
            [-0.0005744044928168696, 0.0025115932933766497, -0.00029040212591161766]))

    def test_check_data_in_data_strucure(self):
        """
        Lastly verify the data being used  to the data structure 
        is correct
        """

        self.assertEqual(mdsys.natoms, 108, "atoms is different from source")
        self.assertEqual(mdsys.mass, 39.948, "mass is different from source")
        self.assertEqual(mdsys.epsilon, 0.2379,
                         "epsilon is different from source")
        self.assertEqual(mdsys.sigma, 3.405, "sigma is different from source")
        self.assertEqual(mdsys.rcut, 8.5, "rcut is different from source")
        self.assertEqual(mdsys.box, 17.1580, "box is different from source")
        self.assertEqual(mdsys.nsteps, 10000, "steps is different from source")
        self.assertEqual(mdsys.dt, 5.0, "dt is different from source")

        #check the 1st number
        self.assertEqual(mdsys.rx[0], 6.67103294321331,"The 1st value of arra_rx[0] is not the same with source")
        self.assertEqual(mdsys.ry[0], -10.6146871435653,"The 1st value of arra_ry[0] is not the same with source")
        self.assertEqual(mdsys.rz[0], 12.6336939877734,"The 1st value of arra_rz[0] is not the same with source")
        self.assertEqual(mdsys.rx[108], -6.65121935702062,"The last value of arra_rx[0] is not the same with source")
        self.assertEqual(mdsys.ry[108], 1.49356278110318,"The last value of arra_ry[0] is not the same with source")
        self.assertEqual(mdsys.rz[108], 20.6354475761263,"The last value of arra_rz[0] is not the same with source")


        #check velocity values
        self.assertEqual(mdsys.vx[0], -1.5643224621482283e-03,"The 1st value of arra_vx[0] is not the same with source")
        self.assertEqual(mdsys.vy[0], 4.8497508563925346e-04,"The 1st value of arra_vy[0] is not the same with source")
        self.assertEqual(mdsys.vz[0], -4.3352481732883966e-04,"The 1st value of arra_vz[0] is not the same with source")
        self.assertEqual(mdsys.vx[108], -7.6107091738481837e-05,"The last value of arra_vx[0] is not the same with source")
        self.assertEqual(mdsys.vy[108], 6.5742688995404971e-04,"The last value of arra_vy[0] is not the same with source")
        self.assertEqual(mdsys.vz[108], -2.9040212591161766e-04,"The last value of arra_vz[0] is not the same with source")

    def test_check_after_azzero(self):
        """
        """
        pass



if __name__ == '__main__':
    
    unittest.main(verbosity=2)
