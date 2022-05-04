-- smiledb.customer_info definition

CREATE TABLE `customer_info` (
  `customer_id` varchar(36) NOT NULL,
  `customer_name` varchar(32) NOT NULL,
  `customer_gender` varchar(20) NOT NULL,
  `customer_identifier` varchar(40) NOT NULL,
  `customer_job` varchar(20) NOT NULL,
  `customer_country` varchar(32) NOT NULL,
  `customer_province` varchar(32) NOT NULL,
  `customer_city` varchar(30) NOT NULL,
  `customer_birthday` varchar(20) NOT NULL,
  `customer_description` varchar(88) NOT NULL,
  `create_time` datetime NOT NULL,
  `update_time` datetime NOT NULL,
  PRIMARY KEY (`customer_id`)
) ENGINE=InnoDB DEFAULT CHARSET=ascii;

-- customer_id : 0089dea66ae84835bad1170b3ef4746b
-- customer_id : 0095f5730eeb491d814265e79877a12d
-- customer_id : 00aacd683acd4719b8b14db4d29c28dc
-- customer_id : 044bed0c49404f6faa50b466040cb016
-- customer_id : 05c2c5ab1619427db5216ea7d1ae8528